//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: HypHIFrsRunData.cc 69223 2013-04-23 12:36:10Z gcosmo $
//
/// \file HypHIFrsRunData.cc
/// \brief Implementation of the HypHIFrsRunData class

#include "HypHIFrsRunData.hh"
#include "HypHIFrsAnalysis.hh"

#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

#include "G4SystemOfUnits.hh"

#include "THypHi_UTrackerHit.hh"
#include "HypHIFrsUTrackerHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIFrsRunData::HypHIFrsRunData(const G4String& name) : G4Run(),namefile(name),fileOut(nullptr),Tree(nullptr),LookCheckFile(false),LookCheckTree(false),CloseDone(false)
{
  if(LookCheckFile==false)
    {
      fileOut = new TFile(namefile,"RECREATE");
      LookCheckFile = true;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIFrsRunData::~HypHIFrsRunData()
{
  Close();
}

void HypHIFrsRunData::Close()
{
  if(CloseDone==false)
    {
      fileOut->cd();
      Tree->Write();
      fileOut->Close();
      fileOut->Delete();
      CloseDone=true;
    }
}

void HypHIFrsRunData::InitTree(const std::vector<G4String>& nameDet)
{
  if(LookCheckTree==false)
    {
      if(LookCheckFile==false)
	{
	  fileOut = new TFile(namefile,"RECREATE");
	  LookCheckFile = true;
	}
      
      fileOut->cd();
      Tree = new TTree("G4Tree","Geant4 Tree");

      fEvent = new THypHi_Event; 
      Tree->Branch("HypHi_Event",&fEvent);
      for(auto& nameBranch : nameDet)
	{
	  TClonesArray* SubEvent_UTracker = new TClonesArray("UTrackerHit",20);
	  Tree->Branch(nameBranch,&SubEvent_UTracker,3200,2);
	  addrCloneArray.push_back(SubEvent_UTracker);
	}

      LookCheckTree = true;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HypHIFrsRunData::FillPerEvent(const G4Event* event)
{
  // // get analysis manager
  // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // //accumulate statistic
  // //

  // for ( G4int i=0; i<kDim; i++) {
  //   // fill histograms
  //   analysisManager->FillH1(i+1, fEdep[i]);
  //   analysisManager->FillH1(kDim+i+1, fTrackLength[i]);

  //   // fill ntuple
  //   analysisManager->FillNtupleDColumn(i, fEdep[i]);
  //   analysisManager->FillNtupleDColumn(kDim+i, fTrackLength[i]);
  // }  

  // analysisManager->AddNtupleRow();  

  unsigned int Nprimary = event->GetNumberOfPrimaryVertex();
  if(Nprimary > 0)
    {
      for(unsigned int iPrimary = 0; iPrimary < Nprimary; ++Nprimary)
	{
	  G4PrimaryVertex* PrimVertex = event->GetPrimaryVertex(iPrimary);
	  if(PrimVertex!=nullptr)
	    {
	      unsigned int Nparticle = PrimVertex->GetNumberOfParticle();
	      fEvent->InteractionPoint_X=PrimVertex->GetX0()/cm;
	      fEvent->InteractionPoint_Y=PrimVertex->GetY0()/cm;
	      fEvent->InteractionPoint_Z=PrimVertex->GetZ0()/cm;

	      for(unsigned int iParticle = 0; iParticle<Nparticle;++iParticle)
		{
		  G4PrimaryParticle* PrimParticle = PrimVertex->GetPrimary(iParticle);
		  if(PrimParticle!=nullptr)
		    {
		      fEvent->BeamNames.push_back(PrimParticle->GetParticleDefinition()->GetParticleName());
		      fEvent->BeamMasses.push_back(PrimParticle->GetMass()/GeV);
		      fEvent->BeamCharges.push_back(PrimParticle->GetCharge());
		      fEvent->BeamMomentums_X.push_back(PrimParticle->GetPx()/GeV);
		      fEvent->BeamMomentums_Y.push_back(PrimParticle->GetPy()/GeV);
		      fEvent->BeamMomentums_Z.push_back(PrimParticle->GetPz()/GeV);
		    }	  
		}
	    }
	}
    }
  G4HCofThisEvent* hce = event->GetHCofThisEvent();
  if (!hce) 
    {
      G4ExceptionDescription msg;
      msg << "No hits collection of this event found." << G4endl; 
      G4Exception("B5EventAction::EndOfEventAction()","B5Code001", JustWarning, msg);
      return;
    }   

  for( unsigned int idCol = 0;idCol<addrCloneArray.size();++idCol)
    {
      HypHIFrsUTrackerHitsCollection* TempCol = dynamic_cast<HypHIFrsUTrackerHitsCollection*>(hce->GetHC(idCol));
      TClonesArray* TempCArray = addrCloneArray[idCol];
      if(TempCol != nullptr)
  	{
  	  G4int nhits = TempCol->entries();

  	  for(G4int ihit = 0 ; ihit<nhits;++ihit)
  	    {
  	      HypHIFrsUTrackerHit* TempHit = (*TempCol)[ihit];
	      UTrackerHit *RootHit = dynamic_cast<UTrackerHit*>(TempCArray->ConstructedAt(TempCArray->GetEntries()));
  	    
	      RootHit->TrackID = TempHit->TrackID; 
	      RootHit->HitPosX = TempHit->HitPosX; 
	      RootHit->HitPosY = TempHit->HitPosY; 
	      RootHit->HitPosZ = TempHit->HitPosZ; 
	      RootHit->ExitPosX = TempHit->ExitPosX; 
	      RootHit->ExitPosY = TempHit->ExitPosY; 
	      RootHit->ExitPosZ = TempHit->ExitPosZ;
	      RootHit->MomX = TempHit->MomX;
	      RootHit->MomY = TempHit->MomY; 
	      RootHit->MomZ = TempHit->MomZ;
	      RootHit->Energy = TempHit->Energy;
	      RootHit->Time = TempHit->Time; 
	      RootHit->Pname = TempHit->Pname;
	      RootHit->Mass = TempHit->Mass;
	    }
  	}
      else
  	{
  	  G4ExceptionDescription msg;
  	  msg << "Some of hits collections of this event not found." << G4endl; 
  	  G4Exception("B5EventAction::EndOfEventAction()","B5Code001", JustWarning, msg);
  	  return;
  	}
    }

  Tree->Fill();
  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HypHIFrsRunData::Reset()
{ 
  fEvent->Zero();
  for( unsigned int i = 0; i<addrCloneArray.size(); ++i )
    addrCloneArray[i]->Clear("C");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
