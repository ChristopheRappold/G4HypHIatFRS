#include "THypHi_PhysicsList.hh"

#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4ios.hh"              

/********************************************************************/
THypHi_PhysicsList::THypHi_PhysicsList(const THypHi_Par& _par): G4VModularPhysicsList(),Par(_par)
{
    
    defaultCutValue = Par.Get_CutValue_Default();
    //SetVerboseLevel(1);
}

/********************************************************************/
THypHi_PhysicsList::~THypHi_PhysicsList(){
}

/********************************************************************/
void THypHi_PhysicsList::ConstructParticle(){
    // In this method, static member functions should be called
    // for all particles which you want to use.
    // This ensures that objects of these particle types will be
    // created in the program. 
    
    ConstructBosons();
    ConstructLeptons();
    ConstructMesons();
    ConstructBaryons();
}

/********************************************************************/
void THypHi_PhysicsList::ConstructBosons(){
    // pseudo-particles
    G4Geantino::GeantinoDefinition();
    G4ChargedGeantino::ChargedGeantinoDefinition();
    
    // gamma
    G4Gamma::GammaDefinition();
}

/********************************************************************/
void THypHi_PhysicsList::ConstructLeptons(){
    // leptons
    G4Electron::ElectronDefinition();
    G4Positron::PositronDefinition();
    G4MuonPlus::MuonPlusDefinition();
    G4MuonMinus::MuonMinusDefinition();
    
    G4NeutrinoE::NeutrinoEDefinition();
    G4AntiNeutrinoE::AntiNeutrinoEDefinition();
    G4NeutrinoMu::NeutrinoMuDefinition();
    G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
}

/********************************************************************/
void THypHi_PhysicsList::ConstructMesons(){
    //  mesons
    G4PionPlus::PionPlusDefinition();
    G4PionMinus::PionMinusDefinition();
    G4PionZero::PionZeroDefinition();
    G4Eta::EtaDefinition();
    G4EtaPrime::EtaPrimeDefinition();
    G4KaonPlus::KaonPlusDefinition();
    G4KaonMinus::KaonMinusDefinition();
    G4KaonZero::KaonZeroDefinition();
    G4AntiKaonZero::AntiKaonZeroDefinition();
    G4KaonZeroLong::KaonZeroLongDefinition();
    G4KaonZeroShort::KaonZeroShortDefinition();
 // skaon+ non-decay Kaon+ 
//     G4VMeson* particle;

//     particle = new G4VMeson (            
// 		     "skaon+",    0.493677*GeV, 5.315e-14*MeV,    +1.*eplus, 
// 		     0,              -1,             0,          
// 		     1,              +1,             0,             
// 		     "meson",               0,             0,            321,
// 		     true,             -1.0,          NULL);
    
}

/********************************************************************/
// #include "TH4L.hh"
// #include "TH3L.hh"
// #include "THe4L.hh"
// #include "THe5L.hh"
// #include "TLambda.hh"
// #include "TTritonStar.hh"
// #include "TnnL.hh"
//
#include "G4AntiLambda.hh"
#include "G4Lambda.hh"
#include "G4SigmaMinus.hh"
#include "G4SigmaPlus.hh"
#include "G4SigmaZero.hh"
#include "G4AntiSigmaMinus.hh"
#include "G4AntiSigmaPlus.hh"
#include "G4AntiSigmaZero.hh"
void THypHi_PhysicsList::ConstructBaryons(){
    // TH4L::H4LDefinition();
    // TH3L::H3LDefinition();
    // THe4L::He4LDefinition();
    // THe5L::He5LDefinition();
    // TLambda::LambdaDefinition();
    // TTritonStar::TritonStarDefinition();
    // TnnL::nnLDefinition();
    //  barions
    G4Proton::ProtonDefinition();
    G4AntiProton::AntiProtonDefinition();
    G4Neutron::NeutronDefinition();
    G4AntiNeutron::AntiNeutronDefinition();
    //
    G4AntiLambda::AntiLambdaDefinition();
    G4Lambda::LambdaDefinition();
    G4SigmaMinus::SigmaMinusDefinition();
    G4SigmaPlus::SigmaPlusDefinition();
    G4SigmaZero::SigmaZeroDefinition();
    G4AntiSigmaMinus::AntiSigmaMinusDefinition();
    G4AntiSigmaPlus::AntiSigmaPlusDefinition();
    G4AntiSigmaZero::AntiSigmaZeroDefinition();

    G4GenericIon::GenericIonDefinition();
//     G4VBaryon* particle;
//     particle = new G4VMeson (            
// 			     "superL",    0.493677*GeV, 5.315e-14*MeV,    +1.*eplus, 
// 			     0,              -1,             0,          
// 			     1,              +1,             0,             
// 			     "meson",               0,             0,            321,
// 			     true,             -1.0,          NULL);


}

/********************************************************************/
void THypHi_PhysicsList::ConstructProcess(){
  std::cout<<" THypHi_PhysicsList::ConstructProcess() "<<std::endl;
  AddTransportation();
  std::cout<<" THypHi_PhysicsList::ConstructProcess() Trancs"<<std::endl;
  ConstructEM();
  std::cout<<" THypHi_PhysicsList::ConstructProcess() EM "<<std::endl;
  ConstructGeneral();
  std::cout<<" THypHi_PhysicsList::ConstructProcess() General"<<std::endl;
}

/********************************************************************/
/********************************************************************/
/********************************************************************/
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"
//#include "G4hLowEnergyIonisation.hh"
//#include "G4hLowEnergyLoss.hh"
#include "G4StepLimiter.hh"



#include "G4EmStandardPhysics.hh"
// #include "G4ParticleDefinition.hh"
// #include "G4ProcessManager.hh"
#include "G4LossTableManager.hh"
#include "G4EmProcessOptions.hh"

// #include "G4ComptonScattering.hh"
// #include "G4GammaConversion.hh"
// #include "G4PhotoElectricEffect.hh"

//#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"

// #include "G4eIonisation.hh"
// #include "G4eBremsstrahlung.hh"
// #include "G4eplusAnnihilation.hh"

// #include "G4MuIonisation.hh"
// #include "G4MuBremsstrahlung.hh"
// #include "G4MuPairProduction.hh"
//#include "G4hBremsstrahlung.hh"
// #include "G4hPairProduction.hh"

#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"

#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4PionPlus.hh"
#include "G4PionMinus.hh"
#include "G4KaonPlus.hh"
#include "G4KaonMinus.hh"
#include "G4Proton.hh"
#include "G4AntiProton.hh"
#include "G4Deuteron.hh"
#include "G4Triton.hh"
#include "G4He3.hh"
#include "G4Alpha.hh"
#include "G4GenericIon.hh"










/********************************************************************/
void THypHi_PhysicsList::ConstructEM(){


   theParticleIterator->reset();
   while( (*theParticleIterator)() ){
     G4ParticleDefinition* particle = theParticleIterator->value();
     G4ProcessManager* pmanager = particle->GetProcessManager();
     G4String particleName = particle->GetParticleName();
     

     if (particleName == "gamma") {

       pmanager->AddDiscreteProcess(new G4GammaConversion);
       pmanager->AddDiscreteProcess(new G4ComptonScattering);
       pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);

     } else if (particleName == "e-") {

       //       pmanager->AddProcess(new G4eMultipleScattering(), -1, 1, 1);
       pmanager->AddProcess(new G4eMultipleScattering(), -1, 1, 1);
       pmanager->AddProcess(new G4eIonisation,           -1, 2, 2);
       //pmanager->AddProcess(new G4eBremsstrahlung(),     -1,-3, 3);
       pmanager->AddProcess(new G4eBremsstrahlung(),     -1,3, 3);

     } else if (particleName == "e+") {

       //pmanager->AddProcess(new G4eMultipleScattering(), -1, 1, 1);
       pmanager->AddProcess(new G4eMultipleScattering(), -1, 1, 1);
       pmanager->AddProcess(new G4eIonisation,           -1, 2, 2);
       //pmanager->AddProcess(new G4eBremsstrahlung,       -1,-3, 3);
       pmanager->AddProcess(new G4eBremsstrahlung,       -1, 3, 3);
       pmanager->AddProcess(new G4eplusAnnihilation,      0,-1, 4);

     } else if (particleName == "mu+" || particleName == "mu-"    ) {

       pmanager->AddProcess(new G4MuMultipleScattering,-1, 1, 1);
       pmanager->AddProcess(new G4MuIonisation,        -1, 2, 2);
       pmanager->AddProcess(new G4MuBremsstrahlung,    -1,-3, 3);
       pmanager->AddProcess(new G4MuPairProduction,    -1,-4, 4);

     } else if (particleName == "alpha" ||
                particleName == "He3") {

       pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
       pmanager->AddProcess(new G4hIonisation,         -1, 2, 2);
       //        G4ionIonisation* ionIoni = new G4ionIonisation();
       //        ionIoni->SetStepFunction(0.1, 20*um);
       //        pmanager->AddProcess(ionIoni,                   -1, 2, 2);

       //       pmanager->AddProcess(new G4ionIonisation,       -1, 2, 2);//<--

     } else if (particleName == "GenericIon") {

       pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
       pmanager->AddProcess(new G4ionIonisation,       -1, 2, 2);

     } else if (particleName == "pi+" ||
                particleName == "pi-" ||
		particleName == "kaon+" ||
                particleName == "kaon-" ||
                particleName == "proton" ) {

       pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
       pmanager->AddProcess(new G4hIonisation,         -1, 2, 2);
       //       pmanager->AddProcess(new G4hBremsstrahlung,     -1,-3, 3);
       //       pmanager->AddProcess(new G4hPairProduction,     -1,-4, 4);

     }
     else if( (!particle->IsShortLived()) && (particle->GetPDGCharge() != 0.0) && (particle->GetParticleName() != "chargedgeantino"))
       {
	 
	 // else if (particleName == "B+" ||
	 if (particleName == "B+" ||
	     particleName == "B-" ||
	     particleName == "D+" ||
	     particleName == "D-" ||
	     particleName == "Ds+" ||
	     particleName == "Ds-" ||
	     particleName == "anti_lambda_c+" ||
	     particleName == "anti_omega-" ||
	     particleName == "anti_proton" ||
	     particleName == "anti_sigma_c+" ||
	     particleName == "anti_sigma_c++" ||
	     particleName == "anti_sigma+" ||
	     particleName == "anti_sigma-" ||
	     particleName == "anti_xi_c+" ||
	     particleName == "anti_xi-" ||
	     particleName == "deuteron" ||
	     particleName == "lambda_c+" ||
	     particleName == "omega-" ||
	     particleName == "sigma_c+" ||
	     particleName == "sigma_c++" ||
	     particleName == "sigma+" ||
	     particleName == "sigma-" ||
	     particleName == "tau+" ||
	     particleName == "tau-" ||
	     particleName == "triton" ||
	     particleName == "xi_c+" ||
	     particleName == "xi-" ) {
	   
	   pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
	   pmanager->AddProcess(new G4hIonisation,         -1, 2, 2);
	 }
	 else
	   {
	     pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
	     pmanager->AddProcess(new G4hIonisation,         -1, 2, 2);
	     
	   }
       }
   }
   
   







//      theParticleIterator->reset();
//      while( (*theParticleIterator)() ){
//  	G4ParticleDefinition* particle = theParticleIterator->value();
//  	G4ProcessManager* pmanager = particle->GetProcessManager();
//  	G4String particleName = particle->GetParticleName();

//  	std::cout<<"come here 1 =="<<particleName<<" "<<particle->GetPDGCharge()<<std::endl;	

//  	if (particleName == "gamma") {
//  	  std::cout<<"come here 2"<<std::endl;	
//  	    // gamma
//   	    pmanager->AddDiscreteProcess(new G4GammaConversion());
//   	    pmanager->AddDiscreteProcess(new G4ComptonScattering());
//   	    pmanager->AddDiscreteProcess(new G4PhotoElectricEffect());
//  	} else if (particleName == "e-") {
//  	  std::cout<<"come here 3"<<std::endl;	
//  	    //electron
//  	    G4VProcess* theeminusMultipleScattering = new G4MultipleScattering();
//  	    G4VProcess* theeminusIonisation         = new G4eIonisation();
//  	    G4VProcess* theeminusBremsstrahlung     = new G4eBremsstrahlung();
//  	    //
//  	    // add processes
//   	    pmanager->AddProcess(theeminusMultipleScattering);
// 	    //   	    pmanager->AddProcess(theeminusIonisation);
//    	    pmanager->AddProcess(theeminusBremsstrahlung);
//  	    //
//  	    // set ordering for AlongStepDoIt
//   	    pmanager->SetProcessOrdering(theeminusMultipleScattering,
//   		    idxAlongStep,1);
// //   	    pmanager->SetProcessOrdering(theeminusIonisation,
// //   		    idxAlongStep,2);
//   	    pmanager->SetProcessOrdering(theeminusBremsstrahlung,
//   		    idxAlongStep,3);      
// //  	    //
// //  	    // set ordering for PostStepDoIt
//   	    pmanager->SetProcessOrdering(theeminusMultipleScattering,
//   		    idxPostStep,1);
// //   	    pmanager->SetProcessOrdering(theeminusIonisation,
// //   		    idxPostStep,2);
//   	    pmanager->SetProcessOrdering(theeminusBremsstrahlung,
//   		    idxPostStep,3);
//  	} else if (particleName == "e+") {
//  	  std::cout<<"come here 4"<<std::endl;	
//  	    //positron
//  	    G4VProcess* theeplusMultipleScattering = new G4MultipleScattering();
//  	    G4VProcess* theeplusIonisation         = new G4eIonisation();
//  	    G4VProcess* theeplusBremsstrahlung     = new G4eBremsstrahlung();
//  	    G4VProcess* theeplusAnnihilation       = new G4eplusAnnihilation();
//  	    //
//  	    // add processes
//   	    pmanager->AddProcess(theeplusMultipleScattering);
// 	    //	    pmanager->AddProcess(theeplusIonisation);
//   	    pmanager->AddProcess(theeplusBremsstrahlung);
//   	    pmanager->AddProcess(theeplusAnnihilation);
// //  	    //
// //  	    // set ordering for AtRestDoIt
//   	    pmanager->SetProcessOrderingToFirst(
//   		    theeplusAnnihilation, idxAtRest);
// //  	    //
// //  	    // set ordering for AlongStepDoIt
//   	    pmanager->SetProcessOrdering(
//   		    theeplusMultipleScattering, idxAlongStep,1);
// //   	    pmanager->SetProcessOrdering(
// //   		    theeplusIonisation, idxAlongStep,2);
//   	    pmanager->SetProcessOrdering(
//   		    theeplusBremsstrahlung,idxAlongStep,3);
// //  	    //
// //  	    // set ordering for PostStepDoIt
//   	    pmanager->SetProcessOrdering(
//   		    theeplusMultipleScattering, idxPostStep,1);
// //   	    pmanager->SetProcessOrdering(
// //   		    theeplusIonisation,idxPostStep,2);
//   	    pmanager->SetProcessOrdering(
//   		    theeplusBremsstrahlung,idxPostStep,3);
//   	    pmanager->SetProcessOrdering(
//   		    theeplusAnnihilation,idxPostStep,4);
//  	} else if( particleName == "mu+" ||
//  		particleName == "mu-"    ) {
//  	  std::cout<<"come here 5"<<std::endl;	
//  	    //muon
//  	    G4VProcess* aMultipleScattering = new G4MultipleScattering();
//  	    G4VProcess* aBremsstrahlung     = new G4MuBremsstrahlung();
//  	    G4VProcess* aPairProduction     = new G4MuPairProduction();
//  	    G4VProcess* anIonisation        = new G4MuIonisation();
//  	    //
//  	    // add processes
// 	    //  	    pmanager->AddProcess(anIonisation);
//   	    pmanager->AddProcess(aMultipleScattering);
//   	    pmanager->AddProcess(aBremsstrahlung);
//   	    pmanager->AddProcess(aPairProduction);
//   	    //
//   	    // set ordering for AlongStepDoIt
//   	    pmanager->SetProcessOrdering(aMultipleScattering, idxAlongStep,1);
// 	    //  	    pmanager->SetProcessOrdering(anIonisation,        idxAlongStep,2);
//   	    pmanager->SetProcessOrdering(aBremsstrahlung,     idxAlongStep,3);
//   	    pmanager->SetProcessOrdering(aPairProduction,     idxAlongStep,4);
//   	    //
//   	    // set ordering for PostStepDoIt
//   	    pmanager->SetProcessOrdering(aMultipleScattering, idxPostStep,1);
// 	    //  	    pmanager->SetProcessOrdering(anIonisation,        idxPostStep,2);
//   	    pmanager->SetProcessOrdering(aBremsstrahlung,     idxPostStep,3);
//   	    pmanager->SetProcessOrdering(aPairProduction,     idxPostStep,4);
//  	} 
//  	else if ((!particle->IsShortLived()) && (particle->GetPDGCharge() != 0.0) && (particle->GetParticleName() != "chargedgeantino")) 
//  	{
//  	  std::cout<<"come here 6"<<std::endl;	
//  		// Low energy ionisation...
//  		// protons, ions, alpha, pions, kaons, generic ion.....
//  		if (particleName != "nu_e" && particleName != "anti_nu_e" &&
//  		    particleName != "nu_mu" && particleName != "anti_nu_mu" &&
//  		    particleName != "pi+" && particleName != "pi-" &&
//  		    particleName != "pi0" && particleName != "eta" &&
//  		    particleName != "eta_prime" && particleName != "kaon+" &&
//  		    particleName != "kaon-" && particleName != "kaon0" &&
//  		    particleName != "kaon0L" && particleName != "kaon0S" &&
//  		    particleName != "anti_kaon0" && particleName != "" &&
//  		    particleName != "proton" && particleName != "anti_proton" &&
//  		    particleName != "neutron" && particleName != "anti_neutron" &&
//  		    particleName != "lambda" && particleName != "L" &&
//  		    particleName != "anti_lambda" && particleName != "sigma-" &&
//  		    particleName != "sigma+" && particleName != "sigma0" &&
//  		    particleName != "anti_sigma+" && particleName != "anti_sigma-" &&
//  		    particleName != "anti_sigma0" &&
//  		    particleName != "B+" && particleName != "B-" &&
//  		    particleName != "D+" && particleName != "D-" &&
//  		    particleName != "Ds+" && particleName != "Ds-" &&
//  		    particleName != "alpha" && particleName != "anti_lambda_c+" &&
//  		    particleName != "anti_omega-" && particleName != "anti_sigma_c+" &&
//  		    particleName != "anti_sigma_c++" && particleName != "anti_xi-" &&
//  		    particleName != "anti_xi_c+" && particleName != "deuteron" &&
//  		    particleName != "lambda_c+" && particleName != "omega-" &&
//  		    particleName != "sigma_c+" && particleName != "sigma_c++" &&
//  		    particleName != "tau+" && particleName != "tau-" &&
//  		    particleName != "triton" && particleName != "xi-" &&
//  		    particleName != "xi_c+" )
//  		  {
//  		    std::cout << "!!!> Low energy ionisation for: " << particleName <<"\n";
//  		    //G4hLowEnergyIonisation* ionisation = new G4hLowEnergyIonisation();
//  		    std::cout<<"come here 7"<<std::endl;	
//  		    G4ionIonisation* ionisation = new G4ionIonisation();
//  		    // ICRU49 models for nuclear SP
// // 		    ionisation ->SetNuclearStoppingPowerModel("ICRU_R49") ;
// //  		    ionisation -> SetNuclearStoppingOn() ;
//  		    // Switch off the Barkas and Bloch corrections
//  		    //ionisation -> SetBarkasOn();
		    
//  		    G4VProcess*  multipleScattering = new G4MultipleScattering();
		    
//    		    pmanager -> AddProcess(multipleScattering, -1,1,1);
// 		    pmanager -> AddProcess(ionisation, -1,2,2);
//  		  } 
//  		else 
//  		  {
//  		    std::cout<<"come here 8"<<std::endl;	
//  			// all others charged particles except geantino     
//  		    G4VProcess* aMultipleScattering = new G4MultipleScattering();
//  		    G4VProcess* anIonisation        = new G4hIonisation();
//  			//
//   			// add processes
// 		    pmanager->AddProcess(anIonisation);
//   		    pmanager->AddProcess(aMultipleScattering);
//   		    //
//   		    // set ordering for AlongStepDoIt
//   		    pmanager->SetProcessOrdering(aMultipleScattering, idxAlongStep,1);
// 		    pmanager->SetProcessOrdering(anIonisation,        idxAlongStep,2);
//   		    //
//   		    // set ordering for PostStepDoIt
//   		    pmanager->SetProcessOrdering(aMultipleScattering,idxPostStep,1);
// 		    pmanager->SetProcessOrdering(anIonisation,idxPostStep,2);
		    
//  		  }
//  	}
//  	else
//  	  {
//  	    std::cout<<"come here 9"<<std::endl;	
//  	    std::cout<<" is shhort "<<particle->IsShortLived()<< "  "<< particle->GetPDGCharge() <<std::endl;
//  	  }
//      }
}

/********************************************************************/
#include "G4Decay.hh"
void THypHi_PhysicsList::ConstructGeneral(){
    // Add Decay Process
    G4Decay* theDecayProcess = new G4Decay();
    theParticleIterator->reset();
    while( (*theParticleIterator)() ){
	G4ParticleDefinition* particle = theParticleIterator->value();
	G4ProcessManager* pmanager = particle->GetProcessManager();
	if (theDecayProcess->IsApplicable(*particle)){
	    pmanager ->AddProcess(theDecayProcess);
	    // set ordering for PostStepDoIt and AtRestDoIt
	    pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
	    pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
	}
    }
}

/********************************************************************/
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4ProductionCuts.hh"
void THypHi_PhysicsList::SetCuts(){
    // These values are used as the default production thresholds
    // for the world volume.
    SetCutsWithDefault();
    //
    G4Region* reg;
    G4ProductionCuts* cuts;
    //
    // Setting cuts for Plastic detectros
    reg = G4RegionStore::GetInstance()->GetRegion("DetectorRegion");
    cuts = new G4ProductionCuts;
    cuts->SetProductionCut(
	    Par.Get_CutValue_Plastic());
    reg->SetProductionCuts(cuts);
    //

    // Setting cuts for Target
    reg = G4RegionStore::GetInstance()->GetRegion("TargetRegion");
    cuts = new G4ProductionCuts;
    cuts->SetProductionCut(
	    Par.Get_CutValue_Target());
    reg->SetProductionCuts(cuts);
}
