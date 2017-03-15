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
// $Id: HypHIFrsDetectorConstruction.cc 77601 2013-11-26 17:08:44Z gcosmo $
// 
/// \file HypHIFrsDetectorConstruction.cc
/// \brief Implementation of the HypHIFrsDetectorConstruction class

#include "HypHIFrsDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
//#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"

// VGM demo
#include "Geant4GM/volumes/Factory.h"
#include "RootGM/volumes/Factory.h"
#include "TGeoManager.h"
// end VGM demo

#include "G4SystemOfUnits.hh"

#include "G4ChordFinder.hh"
#include "G4Mag_UsualEqRhs.hh"

#include "G4ClassicalRK4.hh"
#include "G4HelixExplicitEuler.hh"
#include "G4HelixImplicitEuler.hh"
#include "G4HelixSimpleRunge.hh"
#include "G4CashKarpRKF45.hh"
#include "G4NystromRK4.hh"
#include "G4SimpleHeum.hh"


#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"

#include "HypHIFrsMagneticField.hh"

#include "G4SDManager.hh"

#include "THypHi_SensetiveD.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//G4ThreadLocal G4GlobalMagFieldMessenger* HypHIFrsDetectorConstruction::fMagFieldMessenger = 0; 
G4ThreadLocal HypHIFrsMagneticField* HypHIFrsDetectorConstruction::SksFieldinRoot = 0; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIFrsDetectorConstruction::HypHIFrsDetectorConstruction(const THypHi_Par& _par) : HypHIVDetectorConstruction(_par), fCheckOverlaps(true)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  // ---------------------------------------------------------------------------
  // VGM demo 
  //

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// G4LogicalVolume* HypHIFrsDetectorConstruction::FindVolume(const G4String& name)
// {
//   G4LogicalVolumeStore* lvStore = G4LogicalVolumeStore::GetInstance();
  
//   for (G4int i=0; i<G4int(lvStore->size()); i++) 
//     {
//       G4LogicalVolume* lv = (*lvStore)[i];
//       if (lv->GetName() == name) 
// 	return lv;
//     }

//   G4String text = "ExN03DetectorConstruction:: FindVolume:\n"; 
//   text = text + "    Logical volume " + name + " does not exist.";
//   std::cerr << text << G4endl;
//   return 0;
// }  	       	         

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIFrsDetectorConstruction::~HypHIFrsDetectorConstruction()
{ 

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* HypHIFrsDetectorConstruction::Construct()
{

  G4Colour  white   (1.0, 1.0, 1.0) ;
  G4Colour  grey    (0.5, 0.5, 0.5) ;
  G4Colour  lgrey   (.85, .85, .85) ;
  G4Colour  red     (1.0, 0.0, 0.0) ;
  G4Colour  blue    (0.0, 0.0, 1.0) ;
  G4Colour  cyan    (0.0, 1.0, 1.0) ;
  G4Colour  magenta (1.0, 0.0, 1.0) ;
  G4Colour  yellow  (1.0, 1.0, 0.0) ;
  G4Colour  orange  (.75, .55, 0.0) ;
  G4Colour  lblue   (0.0, 0.0, .75) ;
  G4Colour  lgreen  (0.0, .75, 0.0) ;
  G4Colour  green   (0.0, 1.0, 0.0) ;
  G4Colour  brown   (0.7, 0.4, 0.1) ;

  G4VisAttributes VisDetectorSD(blue);

  // 
  // Import geometry from Root
  //

  // Import geometry from the root file
  new TGeoManager("HypHIFrsa", "Geant4 basic example HypHIFrsa");
  gGeoManager->Import("geometry.root");

  // Import geometry from Root to VGM
  RootGM::Factory rtFactory;
  rtFactory.SetDebug(0);
  rtFactory.Import(gGeoManager->GetTopNode());

  // Export VGM geometry to Geant4
  //
  Geant4GM::Factory g4Factory;
  g4Factory.SetDebug(0);
  rtFactory.Export(&g4Factory);
  
  G4VPhysicalVolume* world = g4Factory.World();

  // Get volumes from logical volume store by name
  //G4LogicalVolume* calorLV = FindVolume("Calorimeter");
  
  G4LogicalVolume* MagFieldLV = FindVolume("MagField");
  G4LogicalVolume* DMagLV = FindVolume("DMag1");
  G4LogicalVolume* VolGapLV = FindVolume("VolGap");
  G4LogicalVolume* SecondMagFieldLV = FindVolume("SecondMagField");
  G4LogicalVolume* SecondMagLV = FindVolume("SecondMag");
  G4LogicalVolume* SetupLV = FindVolume("Setup");
  G4LogicalVolume* IronQuadLV = FindVolume("IronQuad");

  G4Region* aTargetRegion = new G4Region("TargetRegion");

  G4LogicalVolume* TargetLV = FindVolume("Target");
  TargetLV->SetRegion(aTargetRegion);
  aTargetRegion->AddRootLogicalVolume(TargetLV);

  G4Region* aDetectorRegion = new G4Region("DetectorRegion");
 
  std::vector<G4String> NameSD = {"START","TR0","TR1","DC1","TR2","DC2","DC3","TOFP","DC2STOP","STOP"};

  for(auto& CurrentName : NameSD)
    {
      G4LogicalVolume* UTracker = FindVolume(CurrentName);

      UTracker->SetRegion(aDetectorRegion);
      aDetectorRegion->AddRootLogicalVolume(UTracker);

      UTracker->SetVisAttributes(VisDetectorSD);
    }  

  NameDetectorsSD = NameSD;
  
  // Visualization attributes
  //
  G4LogicalVolume* worldLV = world->GetLogicalVolume();
  worldLV->SetVisAttributes (G4VisAttributes::Invisible);
  
  if(MagFieldLV)
    MagFieldLV->SetVisAttributes(G4VisAttributes::Invisible);
  if(DMagLV)
    DMagLV->SetVisAttributes(G4VisAttributes::Invisible);
  if(VolGapLV)
    VolGapLV->SetVisAttributes(G4VisAttributes::Invisible);
  if(SecondMagFieldLV)
    SecondMagFieldLV->SetVisAttributes(G4VisAttributes::Invisible);
  if(SecondMagLV)
    SecondMagLV->SetVisAttributes(G4VisAttributes::Invisible);
  if(SetupLV)
    SetupLV->SetVisAttributes(G4VisAttributes::Invisible);
  if(IronQuadLV)
    IronQuadLV->SetVisAttributes(G4VisAttributes::Invisible);

  

  // G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  // simpleBoxVisAtt->SetVisibility(true);
  // if (calorLV) calorLV->SetVisAttributes(simpleBoxVisAtt);
  
  return world;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HypHIFrsDetectorConstruction::DefineMaterials()
{ 
// Dummy, as materials are imported via VGM
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* HypHIFrsDetectorConstruction::DefineVolumes()
{
// Dummy, as geometry is imported via VGM

  return 0;
}

  //
  // end VGM demo
  //---------------------------------------------------------------------------


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HypHIFrsDetectorConstruction::ConstructSDandField()
{ 
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.

  // G4ThreeVector fieldValue = G4ThreeVector();
  // fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  // fMagFieldMessenger->SetVerboseLevel(1);

  G4SDManager *SDman = G4SDManager::GetSDMpointer();

  for(auto& CurrentName : NameDetectorsSD)
    {
      G4LogicalVolume* UTracker = FindVolume(CurrentName);
      THypHi_SD_UTracker* SD = new THypHi_SD_UTracker(CurrentName,CurrentName);
      //SD->Init();
      SDman->AddNewDetector(SD);
      UTracker->SetSensitiveDetector(SD);
    }  



  G4FieldManager* fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();

  SksFieldinRoot = new HypHIFrsMagneticField("./field/SksPlusField_1000A.root");
  
  double SKS_field1_value = Par.Get_Geometry_SKSField1();
  double SKS_field2_value = Par.Get_Geometry_SKSField2();

  std::cout<<" Sks field :"<<SKS_field1_value<<" "<<SKS_field2_value<<std::endl;

  SksFieldinRoot->InitField(-SKS_field1_value/0.8016,true,SKS_field2_value);
  fieldMgr->SetDetectorField(SksFieldinRoot);

  double pointTest[3] = {0.,0.,90.*cm};
  double fieldTest[3] = {0.,0.,0.};
  SksFieldinRoot->GetFieldValue(pointTest,fieldTest);
  std::cout<<" Field 1 :"<<fieldTest[1]/tesla<<" T | ";
  pointTest[2] = 300.*cm;
  SksFieldinRoot->GetFieldValue(pointTest,fieldTest);
  std::cout<<" Field 2 :"<<fieldTest[1]/tesla<<" T"<<std::endl;
  
  
  G4Mag_UsualEqRhs* pMagFldEquation = new G4Mag_UsualEqRhs(SksFieldinRoot);
  //G4MagIntegratorStepper* fStepper = new G4NystromRK4( pMagFldEquation );

  G4MagIntegratorStepper* fStepper = new G4SimpleHeum(pMagFldEquation,8);

  G4ChordFinder *pChordFinder = new G4ChordFinder(SksFieldinRoot,1.e-2*mm, fStepper);
  pChordFinder->SetDeltaChord(1.0e-1*mm);
  
  fieldMgr->SetChordFinder(pChordFinder);

  // G4LogicalVolume* SetupLV = FindVolume("Setup");
  // SetupLV->SetFieldManager(fieldMgr,true);

  // Register the field messenger for deleting
  G4AutoDelete::Register(SksFieldinRoot);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
