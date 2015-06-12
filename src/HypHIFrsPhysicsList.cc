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
// $Id$
//
/// \file HypHIFrsPhysicsList.cc
/// \brief Implementation of the HypHIFrsPhysicsList class

#include "HypHIFrsPhysicsList.hh"

// #include "G4Geantino.hh"
// #include "G4ChargedGeantino.hh"

// #include "G4Gamma.hh"

// #include "G4Electron.hh"
// #include "G4Positron.hh"
// #include "G4NeutrinoE.hh"
// #include "G4AntiNeutrinoE.hh"

// #include "G4MuonPlus.hh"
// #include "G4MuonMinus.hh"
// #include "G4NeutrinoMu.hh"
// #include "G4AntiNeutrinoMu.hh"

// #include "G4PionPlus.hh"
// #include "G4PionMinus.hh"
// #include "G4PionZero.hh"

// #include "G4KaonPlus.hh"
// #include "G4KaonMinus.hh"
// #include "G4KaonZero.hh"
// #include "G4AntiKaonZero.hh"
// #include "G4KaonZeroLong.hh"
// #include "G4KaonZeroShort.hh"

// #include "G4Proton.hh"
// #include "G4Neutron.hh"
// #include "G4Lambda.hh"
// #include "G4SigmaMinus.hh"
// #include "G4SigmaPlus.hh"
// #include "G4SigmaZero.hh"

// #include "G4Deuteron.hh"
// #include "G4Triton.hh"
// #include "G4Alpha.hh"
// #include "G4GenericIon.hh"


// #include "G4DecayPhysics.hh"


//#include "HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4HadronPhysicsINCLXX.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"

#include "G4IonBinaryCascadePhysics.hh"
#include "G4IonPhysics.hh"
#include "G4IonINCLXXPhysics.hh"

#include "G4EmStandardPhysics.hh"
//#include "GammaPhysics.hh"

#include "HypernuclearPhysics.hh"

//#include "EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"


#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4ProductionCuts.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


HypHIFrsPhysicsList::HypHIFrsPhysicsList(const THypHi_Par& _par) : G4VModularPhysicsList(),Par(_par)
{
  G4int verb = 1;
  SetVerboseLevel(verb);
  
  // EM physics
  RegisterPhysics(new G4EmStandardPhysics());

  // Hadron Elastic scattering
  //RegisterPhysics( new HadronElasticPhysicsHP(verb) );
  
  // Hadron Inelastic Physics
  ////RegisterPhysics( new G4HadronPhysicsFTFP_BERT_HP(verb));
  //RegisterPhysics( new G4HadronPhysicsQGSP_BIC_HP(verb));
  ////RegisterPhysics( new G4HadronInelasticQBBC(verb));        
  ////RegisterPhysics( new G4HadronPhysicsINCLXX(verb));
  
  // Ion Physics
  RegisterPhysics( new G4IonPhysics(verb));
  ////RegisterPhysics( new G4IonINCLXXPhysics(verb));

  RegisterPhysics( new G4IonBinaryCascadePhysics());
  //RegisterPhysics( new G4EmExtraPhysics());
  RegisterPhysics( new G4HadronElasticPhysics());
  //RegisterPhysics( new G4StoppingPhysics());
  RegisterPhysics( new G4HadronPhysicsQGSP_BIC());

  RegisterPhysics( new HypernuclearPhysics("Hypernuclear",Par));

    
  // Gamma-Nuclear Physics
  //RegisterPhysics( new GammaPhysics("gamma"));
  
  // // EM physics
  // RegisterPhysics(new EmStandardPhysics());
  
  // Decay
  RegisterPhysics(new G4DecayPhysics());

  // Radioactive decay
  RegisterPhysics(new G4RadioactiveDecayPhysics());      


  


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIFrsPhysicsList::~HypHIFrsPhysicsList()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void HypHIFrsPhysicsList::ConstructParticle()
// {
//   // In this method, static member functions should be called
//   // for all particles which you want to use.
//   // This ensures that objects of these particle types will be
//   // created in the program. 


//   G4Geantino::GeantinoDefinition();
//   G4ChargedGeantino::ChargedGeantinoDefinition();

//   // gamma
//   G4Gamma::GammaDefinition();
  
//   // leptons
//   G4Electron::ElectronDefinition();
//   G4Positron::PositronDefinition();
//   G4MuonPlus::MuonPlusDefinition();
//   G4MuonMinus::MuonMinusDefinition();

//   G4NeutrinoE::NeutrinoEDefinition();
//   G4AntiNeutrinoE::AntiNeutrinoEDefinition();
//   G4NeutrinoMu::NeutrinoMuDefinition();
//   G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();  

//   // mesons
//   G4PionPlus::PionPlusDefinition();
//   G4PionMinus::PionMinusDefinition();
//   G4PionZero::PionZeroDefinition();

//   G4KaonPlus::KaonPlusDefinition();
//   G4KaonMinus::KaonMinusDefinition();
//   G4KaonZero::KaonZeroDefinition();
//   G4AntiKaonZero::AntiKaonZeroDefinition();
//   G4KaonZeroLong::KaonZeroLongDefinition();
//   G4KaonZeroShort::KaonZeroShortDefinition();

//   // barions
//   G4Proton::ProtonDefinition();
//   G4Neutron::NeutronDefinition();
  
//   G4Lambda::LambdaDefinition();
//   G4SigmaMinus::SigmaMinusDefinition();
//   G4SigmaPlus::SigmaPlusDefinition();
//   G4SigmaZero::SigmaZeroDefinition();

//   // ions
//   G4Deuteron::DeuteronDefinition();
//   G4Triton::TritonDefinition();
//   G4Alpha::AlphaDefinition();
//   G4GenericIon::GenericIonDefinition();

//   RegisterPhysics(new G4DecayPhysics());


// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void HypHIFrsPhysicsList::ConstructProcess()
// {
//   // Define transportation process

//   AddTransportation();
// }

void HypHIFrsPhysicsList::SetCuts()
{ 
  SetCutsWithDefault();

  G4double lowLimit = 0.5 * MeV;
  G4double highLimit = 4. * GeV;
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(lowLimit, highLimit);

  SetCutValue(10*mm, "gamma");
  SetCutValue(10*mm, "e-");
  SetCutValue(10*mm, "e+");
  //G4VUserPhysicsList::SetCuts();
  
  // SetCutValue(10*m, "proton");
  //SetCutValue(1*cm, "Ion");

  G4Region* reg;
  G4ProductionCuts* cuts;
  //
  // Setting cuts for Plastic detectros
  reg = G4RegionStore::GetInstance()->GetRegion("DetectorRegion");
  cuts = new G4ProductionCuts;
  cuts->SetProductionCut(Par.Get_CutValue_Plastic());
  reg->SetProductionCuts(cuts);
  //

  // Setting cuts for Target
  reg = G4RegionStore::GetInstance()->GetRegion("TargetRegion");
  cuts = new G4ProductionCuts;
  cuts->SetProductionCut(Par.Get_CutValue_Target());
  reg->SetProductionCuts(cuts);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
