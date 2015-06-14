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
// $Id: HypHIFrsActionInitialization.cc 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file HypHIFrsActionInitialization.cc
/// \brief Implementation of the HypHIFrsActionInitialization class

#include "HypHIFrsActionInitialization.hh"
#include "HypHIFrsPrimaryGeneratorAction.hh"
#include "HypHIFrsRunAction.hh"
#include "HypHIFrsEventAction.hh"
#include "HypHIFrsStackingAction.hh"
#include "HypHIFrsDetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIFrsActionInitialization::HypHIFrsActionInitialization (HypHIFrsGeometryController* geoControl, const THypHi_Par& ConfFile, const G4String& Out, bool In) : G4VUserActionInitialization(),fGeoController(geoControl),Par(ConfFile),OutputFile(Out),InputCIN(In)
{

  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIFrsActionInitialization::~HypHIFrsActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HypHIFrsActionInitialization::BuildForMaster() const
{
  SetUserAction(new HypHIFrsRunAction(OutputFile, fGeoController->GetNameDetectors()));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HypHIFrsActionInitialization::Build() const
{
  SetUserAction(new HypHIFrsPrimaryGeneratorAction(Par,InputCIN));

  SetUserAction(new HypHIFrsRunAction(OutputFile, fGeoController->GetNameDetectors()));
  
  HypHIFrsEventAction* eventAction = new HypHIFrsEventAction( fGeoController->GetNameDetectors());
  SetUserAction(eventAction);

  SetUserAction(new HypHIFrsStackingAction());
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
