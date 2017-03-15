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
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "HypHIFrsStackingAction.hh"

#include "G4VProcess.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"
//#include "HypernuclearPhysics.hh"
#include "G4SystemOfUnits.hh"

#include "TH3L.hh"
#include "TH4L.hh"
#include "THe4L.hh"
#include "THe5L.hh"
#include "TTritonStar.hh"
#include "TnnL.hh"

#include "TMath.h"
//#include <tuple>
//#include <functional>


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIFrsStackingAction::HypHIFrsStackingAction() : G4UserStackingAction(),beamAxis(0,0,1)

{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIFrsStackingAction::~HypHIFrsStackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
HypHIFrsStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
  G4ParticleDefinition* def = aTrack->GetDefinition();
  if( def == G4Lambda::Definition() || def == TH3L::Definition() || def == TH4L::Definition() || def == THe4L::Definition() || 
      def == THe5L::Definition() || def == TnnL::Definition() || def == TTritonStar::Definition())
    { 
      // G4cout<<" Stacking ClassifyNewTrack:"<<G4endl;
      // G4cout<<"Find Lambda :"<<aTrack->GetTrackID()<<G4endl;
      G4int mother_id = aTrack->GetTrackID();
      const G4DynamicParticle* tempParticle = aTrack->GetDynamicParticle(); 
      //tempParticle->DumpInfo();
      // G4cout<<" Vtx Position"<<aTrack->GetPosition()<<G4endl;
      // G4cout<<" Time :"<<aTrack->GetProperTime()/ns<<" "<<" "<<aTrack->GetLocalTime()/ns<<" "<<aTrack->GetGlobalTime()/ns<<G4endl;
      
      auto it_mother = mother_daugthersInfo.find(mother_id);
      if(it_mother==mother_daugthersInfo.end())
	{
	  Daugthers_Info newInfo;
	  mother_daugthersInfo.insert(std::pair<G4int,Daugthers_Info>(mother_id,newInfo));
	}
    }
  
  auto momDir = aTrack->GetMomentumDirection();
  if(momDir.isNear(beamAxis,1e-8))
    {
      int PDG = def->GetPDGEncoding();
      int Tid = aTrack->GetTrackID();
      auto optic_key = std::tie<int,int>(Tid,PDG);
      auto it_ion = optic_lines.find(optic_key);
      if(it_ion != optic_lines.end())
	{
	  auto temp_pos = aTrack->GetPosition();
	  double TempL = aTrack->GetTrackLength();
	  double TempXZ = TMath::ATan(momDir.getX()/momDir.getZ());
	  double TempYZ = TMath::ATan(momDir.getY()/momDir.getZ());
	  double TempX = temp_pos.getX();
	  double TempY = temp_pos.getY();
	  auto new_point = std::tie<double,double,double,double,double>(TempL,TempXZ,TempYZ,TempX,TempY);
	  it_ion->second.push_back(new_point);
	}
      else
	{
	  auto it_pdg = list_PDGSelected.find(PDG);
	  if(it_pdg == list_PDGSelected.end())
	    {
	      auto temp_pos = aTrack->GetPosition();
	      double TempL = aTrack->GetTrackLength();
	      double TempXZ = TMath::ATan(momDir.getX()/momDir.getZ());
	      double TempYZ = TMath::ATan(momDir.getY()/momDir.getZ());
	      double TempX = temp_pos.getX();
	      double TempY = temp_pos.getY();
	      auto new_point = std::tie<double,double,double,double,double>(TempL,TempXZ,TempYZ,TempX,TempY);
	      std::vector<std::tuple<double,double,double,double,double> > temp_vec(1,new_point);
	      optic_lines.insert(std::pair<std::tuple<int,int>,std::vector<std::tuple<double,double,double,double,double> > >(optic_key,temp_vec));
	      
	    }
	}
      // G4int PDG = def->GetPDGEncoding();
      // auto it_PDG = list_PDGSelected.find(PDG);
      // if(it_PDG != list_PDGSelected.end())
      // 	{
      // 	  {
	    
      // 	  }
      // 	}
    }
  if(aTrack->GetParentID()>0)
    {
      //G4cout<<"Process :"<<aTrack->GetCreatorProcess()->GetProcessName()<<G4endl;
      if(aTrack->GetCreatorProcess()->GetProcessName()=="Decay")
	{
	  auto it_mother = mother_daugthersInfo.find(aTrack->GetParentID());
	  
	  if(it_mother!=mother_daugthersInfo.end())
	    { // particle is secondary
	      //G4cout<<"Stacking: "<<aTrack->GetCreatorProcess()->GetProcessName()<<G4endl;
	      const G4DynamicParticle* tempParticle = aTrack->GetDynamicParticle(); 
	      //tempParticle->DumpInfo();
	      //G4cout<<" Vtx Position"<<aTrack->GetPosition()<<G4endl;
	      //G4cout<<" Time :"<<aTrack->GetProperTime()/ns<<" "<<" "<<aTrack->GetLocalTime()/ns<<" "<<aTrack->GetGlobalTime()/ns<<G4endl;
	      if(it_mother->second.mass_daughters.size()==0)
		{
		  it_mother->second.secondary_vertex = aTrack->GetPosition();
		  it_mother->second.decaytime = aTrack->GetGlobalTime();
		  it_mother->second.mom_daughters.push_back(aTrack->GetMomentum());
		  it_mother->second.mass_daughters.push_back(tempParticle->GetMass());
		  it_mother->second.name_daughters.push_back(tempParticle->GetParticleDefinition()->GetParticleName());
		  it_mother->second.charge_daughters.push_back(tempParticle->GetCharge());
		  it_mother->second.trackID_daughters.push_back(aTrack->GetTrackID());
		}
	      else
		{
		  if(it_mother->second.secondary_vertex != aTrack->GetPosition())
		    {
		      G4cout<<"E > Secondary Vertex position different !"<<it_mother->second.secondary_vertex<<" "<<aTrack->GetPosition()<<G4endl;
		    }
		  
		  it_mother->second.mom_daughters.push_back(aTrack->GetMomentum());
		  it_mother->second.mass_daughters.push_back(tempParticle->GetMass());
		  it_mother->second.name_daughters.push_back(tempParticle->GetParticleDefinition()->GetParticleName());
		  it_mother->second.charge_daughters.push_back(tempParticle->GetCharge());
		  it_mother->second.trackID_daughters.push_back(aTrack->GetTrackID());
		}
	    }
	}
    }
  //G4cout<<" ---- "<<G4endl;

  return fUrgent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HypHIFrsStackingAction::NewStage()
{
  // G4cout << "Number of Scintillation photons produced in this event : "
  //        << fScintillationCounter << G4endl;
  // G4cout << "Number of Cerenkov photons produced in this event : "
  //        << fCerenkovCounter << G4endl;

  //G4cout<<" Decay in the event :"<<G4endl;
  // for(const auto& elem : mother_daugthersInfo)
  //   {
  //     elem.second.Print();
  //   }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HypHIFrsStackingAction::PrepareNewEvent()
{
  mother_daugthersInfo.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool HypHIFrsStackingAction::Get_MotherInfo(G4int id) const
{
  auto it_motherOut = mother_daugthersInfo.find(id);

  return it_motherOut != mother_daugthersInfo.end();
}

const Daugthers_Info HypHIFrsStackingAction::Get_DaugthersInfo(G4int id) const
{

  auto it_motherOut = mother_daugthersInfo.find(id);
  if(it_motherOut!=mother_daugthersInfo.end())
    {
      return it_motherOut->second;
    }
  else
    {
      G4cout<<"E> Stack Info no daugther info for this mother ID "<<id<<G4endl;
    }


  Daugthers_Info temp;
  return temp;
}
