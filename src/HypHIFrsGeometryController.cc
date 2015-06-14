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
// HypHIFrs development is supported by the
// Italian Institute for Nuclear Physics (INFN)
// in the framework of the MC-INFN Project

#include "HypHIFrsGeometryController.hh"
#include "HypHIFrsDetectorConstruction.hh"
#include "HypHIPhase0DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4VUserParallelWorld.hh"
//#include "G4ThreeVector.hh"


/////////////////////////////////////////////////////////////////////////////
HypHIFrsGeometryController::HypHIFrsGeometryController(const THypHi_Par& _par):Par(_par)
{

}

/////////////////////////////////////////////////////////////////////////////
HypHIFrsGeometryController::~HypHIFrsGeometryController()
{}

/////////////////////////////////////////////////////////////////////////////
void HypHIFrsGeometryController::SetGeometry(G4String name)
{
  G4cout <<"Activating geometry " << name << G4endl;
  if(name == "HypHIFrs")
    {
      registerGeometry(new HypHIFrsDetectorConstruction());
    }
  else if(name == "Phase0")
    {
      registerGeometry(new HypHIPhase0DetectorConstruction());
    }
  else if(name == "Phase0.5")
    {
      registerGeometry(new HypHIFrsPhase0DetectorConstruction());
    }
  else
    {
      G4cout <<"Unknown geometry: " << name << ". Geometry not changed." << G4endl;
    }
}

/////////////////////////////////////////////////////////////////////////////
void HypHIFrsGeometryController::registerGeometry(G4VUserDetectorConstruction *detector)
{
  G4RunManager *runManager = G4RunManager::GetRunManager();
  runManager -> SetUserInitialization(detector);
  runManager -> GeometryHasBeenModified();
}

