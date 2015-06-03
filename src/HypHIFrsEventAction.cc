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
// $Id: HypHIFrsEventAction.cc 75604 2013-11-04 13:17:26Z gcosmo $
// 
/// \file HypHIFrsEventAction.cc
/// \brief Implementation of the HypHIFrsEventAction class

#include "HypHIFrsEventAction.hh"
#include "HypHIFrsRunAction.hh"
#include "HypHIFrsAnalysis.hh"
#include "HypHIFrsRunData.hh"

#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "HypHIFrsUTrackerHit.hh"
#include "THypHi_SensetiveD.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIFrsEventAction::HypHIFrsEventAction(const std::vector<G4String>& name) : G4UserEventAction(),nameDetector(name)
{

  // G4SDManager *SDman = G4SDManager::GetSDMpointer();  

  // for(const auto& nameDetector : NameDetectors)
  //   {
  //     THypHi_SensetiveD* tempD = dynamic_cast<THypHi_SensetiveD*>(SDman->FindSensitiveDetector(nameDetector));
  //     TClonesArray* tempArray = tempD->Hits;
      
  //     list_Arrays.push_back(tempArray);
  //   }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIFrsEventAction::~HypHIFrsEventAction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HypHIFrsEventAction::BeginOfEventAction(const G4Event* /*event*/)
{  
  // for(auto&  array : list_Arrays)
  //   array.Clear("C");

  if(HCID.size()!=nameDetector.size())
    {
      G4SDManager* sdManager = G4SDManager::GetSDMpointer();
      for(auto& name : nameDetector)
	{
	  G4String tempName(name);
	  tempName+="/UTrackerColl";
	  HCID.push_back(sdManager->GetCollectionID(tempName));
	}
    }
  HypHIFrsRunData* runData = dynamic_cast<HypHIFrsRunData*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  runData->Reset();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HypHIFrsEventAction::EndOfEventAction(const G4Event* event)
{
  HypHIFrsRunData* runData = dynamic_cast<HypHIFrsRunData*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  runData->FillPerEvent(event);

  
  // G4HCofThisEvent* hce = event->GetHCofThisEvent();
  // if (!hce) 
  //   {
  //     G4ExceptionDescription msg;
  //     msg << "No hits collection of this event found." << G4endl; 
  //     G4Exception("B5EventAction::EndOfEventAction()","B5Code001", JustWarning, msg);
  //     return;
  //   }   


  // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // for( auto idCol : HCID)
  //   {
  //     HypHIFrsUTrackerHitsCollection* TempCol = dynamic_cast<HypHIFrsUTrackerHitsCollection*>(hce->GetHC(idCol));
  //     if(TempCol != nullptr)
  // 	{
  // 	  G4int nhits = TempCol->entries();
  // 	  for(G4int ihit = 0 ; ihit<nhits;++ihit)
  // 	    {
  // 	      HypHIFrsUTrackerHit* TempHit = (*TempCol)[ihit];
  // 	      analysisManager->FillNtupleIColumn(0, event->GetEventID());
  // 	      analysisManager->FillNtupleIColumn(1, TempHit->LayerID);
  // 	      analysisManager->FillNtupleIColumn(2, ihit);
  // 	      analysisManager->FillNtupleIColumn(3, TempHit->TrackID);
  // 	      analysisManager->FillNtupleDColumn(4, TempHit->HitPosX);
  // 	      analysisManager->FillNtupleDColumn(5, TempHit->HitPosY);
  // 	      analysisManager->FillNtupleDColumn(6, TempHit->HitPosZ);
  // 	      analysisManager->FillNtupleDColumn(7, TempHit->MomX);
  // 	      analysisManager->FillNtupleDColumn(8, TempHit->MomY);
  // 	      analysisManager->FillNtupleDColumn(9, TempHit->MomZ);
  // 	      analysisManager->FillNtupleDColumn(10, 0.983);  
  // 	      analysisManager->AddNtupleRow();  
  // 	    }
  // 	}
  //     else
  // 	{
  // 	  G4ExceptionDescription msg;
  // 	  msg << "Some of hits collections of this event not found." << G4endl; 
  // 	  G4Exception("B5EventAction::EndOfEventAction()","B5Code001", JustWarning, msg);
  // 	  return;
  // 	}
  //   }


  // G4RunManager* run = G4RunManager::GetRunManager();
  // const HypHIFrsRunAction* UserRun = dynamic_cast<const HypHIFrsRunAction*>(run->GetUserRunAction());
  // UserRun->Fill();
  // Accumulate statistics
  //

  // get analysis manager
  // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // // fill histograms
  // analysisManager->FillH1(1, fEnergyAbs);
  // analysisManager->FillH1(2, fEnergyGap);
  // analysisManager->FillH1(3, fTrackLAbs);
  // analysisManager->FillH1(4, fTrackLGap);
  
  // // fill ntuple
  // analysisManager->FillNtupleDColumn(0, fEnergyAbs);
  // analysisManager->FillNtupleDColumn(1, fEnergyGap);
  // analysisManager->FillNtupleDColumn(2, fTrackLAbs);
  // analysisManager->FillNtupleDColumn(3, fTrackLGap);
  // analysisManager->AddNtupleRow();  
  
  // // Print per event (modulo n)
  // //
  // G4int eventID = event->GetEventID();
  // G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  // if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
  //   G4cout << "---> End of event: " << eventID << G4endl;     

  //   G4cout
  //      << "   Absorber: total energy: " << std::setw(7)
  //                                       << G4BestUnit(fEnergyAbs,"Energy")
  //      << "       total track length: " << std::setw(7)
  //                                       << G4BestUnit(fTrackLAbs,"Length")
  //      << G4endl
  //      << "        Gap: total energy: " << std::setw(7)
  //                                       << G4BestUnit(fEnergyGap,"Energy")
  //      << "       total track length: " << std::setw(7)
  //                                       << G4BestUnit(fTrackLGap,"Length")
  //      << G4endl;
  // }
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
