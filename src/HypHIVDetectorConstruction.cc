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
// $Id: HypHIVDetectorConstruction.cc 77601 2013-11-26 17:08:44Z gcosmo $
// 
/// \file HypHIVDetectorConstruction.cc
/// \brief Implementation of the HypHIVDetectorConstruction class

#include "HypHIVDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4LogicalVolume.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIVDetectorConstruction::HypHIVDetectorConstruction(const THypHi_Par& _par) : G4VUserDetectorConstruction(), Par(_par)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  // ---------------------------------------------------------------------------
  // VGM demo 
  //

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const std::vector<G4String>& HypHIVDetectorConstruction::GetNameDetectors() const
{
  return NameDetectorsSD;
}


G4LogicalVolume* HypHIVDetectorConstruction::FindVolume(const G4String& name)
{
  G4LogicalVolumeStore* lvStore = G4LogicalVolumeStore::GetInstance();
  
  for (G4int i=0; i<G4int(lvStore->size()); i++) 
    {
      G4LogicalVolume* lv = (*lvStore)[i];
      if (lv->GetName() == name) 
	return lv;
    }

  G4String text = "ExN03DetectorConstruction:: FindVolume:\n"; 
  text = text + "    Logical volume " + name + " does not exist.";
  std::cerr << text << G4endl;
  return 0;
}  	       	         

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIVDetectorConstruction::~HypHIVDetectorConstruction()
{ 

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

