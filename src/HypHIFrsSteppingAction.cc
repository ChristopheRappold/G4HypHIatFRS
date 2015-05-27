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
// $Id: HypHIFrsSteppingAction.cc 68058 2013-03-13 14:47:43Z gcosmo $
// 
/// \file HypHIFrsSteppingAction.cc
/// \brief Implementation of the HypHIFrsSteppingAction class

#include "HypHIFrsSteppingAction.hh"
#include "HypHIFrsEventAction.hh"
#include "HypHIFrsDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIFrsSteppingAction::HypHIFrsSteppingAction( const HypHIFrsDetectorConstruction* detectorConstruction, HypHIFrsEventAction* eventAction) : G4UserSteppingAction(),
															 fDetConstruction(detectorConstruction),
															 fEventAction(eventAction)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIFrsSteppingAction::~HypHIFrsSteppingAction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HypHIFrsSteppingAction::UserSteppingAction(const G4Step* step)
{
// Collect energy and track length step by step

  // G4RunManager* run = G4RunManager::GetRunManager();
  // const HypHIFrsRunAction* UserRun = dynamic_cast<const HypHIFrsRunAction*>(run->GetUserRunAction());

  

  // get volume of the current step
  // G4VPhysicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  
  // // energy deposit
  // G4double edep = step->GetTotalEnergyDeposit();
  
  // // step length
  // G4double stepLength = 0.;
  // if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) 
  //   {
  //     stepLength = step->GetStepLength();
  //   }
      
  // if ( volume == fDetConstruction->GetAbsorberPV() ) 
  //   {
  //     fEventAction->AddAbs(edep,stepLength);
  //   }
  
  // if ( volume == fDetConstruction->GetGapPV() ) 
  //   {
  //     fEventAction->AddGap(edep,stepLength);
  //   }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
