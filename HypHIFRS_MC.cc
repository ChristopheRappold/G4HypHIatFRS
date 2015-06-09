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
// $Id: exampleHypHIFrs.cc 75215 2013-10-29 16:07:06Z gcosmo $
//
/// \file exampleHypHIFrs.cc
/// \brief Main program of the HypHIFrs example

#include "HypHIFrsDetectorConstruction.hh"
#include "HypHIFrsActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "FTFP_BERT.hh"
#include "HypHIFrsPhysicsList.hh"
#include "G4StepLimiterPhysics.hh"


#include "Randomize.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "THypHi_ParCreator.hh"
#include <getopt.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

namespace 
{
  void PrintUsage() 
  {
    G4cerr << " Usage: " << G4endl;
    G4cerr << " exampleHypHIFrs [-m macro ] [-u UIsession] [-t nThreads]" << G4endl;
    G4cerr << "   note: -t option is available only for multi-threaded mode."
	   << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

static struct option optlong[] = 
  {
    {"help",0,NULL,'h'},
    {"cin",0,NULL,'c'},
    {"macro",1,NULL,'m'},
    {"session",1,NULL,'u'},
    {"mthread",1,NULL,'t'},
    {"event",1,NULL,'e'},
    {"ip",1,NULL,'i'},
    {"output",1,NULL,'o'},
  };



int main(int argc,char** argv)
{
  // Evaluate arguments
  //
  if ( argc > 7 ) 
    {
      PrintUsage();
      return 1;
    }
  
  G4String macro;
  G4String session;
  G4int nThreads = 0;
  G4int nEvent = 0;
  bool Input_CIN = false;
  G4String ParamInputFileName = "HypHIMC_ParInput.txt";
  G4String OutputFileName = "HypHIMC_OutNew.root";
  
  int option_char;
  while ((option_char = getopt_long (argc,argv,"+hcm:u:t:e:i:o:",optlong,NULL)) != EOF)
    switch (option_char)
      {  
      case 'h' : PrintUsage(); return 1; break;
      case 'm' : macro = optarg; break;
      case 'u' : session = optarg; break;
      case 't' : nThreads = G4UIcommand::ConvertToInt(optarg); break;
      case 'e' : nEvent = G4UIcommand::ConvertToInt(optarg); break;
      case 'c' : Input_CIN = true; break;
      case 'i' : ParamInputFileName = optarg; break;
      case 'o' : OutputFileName = optarg; break;
      }


  THypHi_ParCreator Parser;
  Parser.Init(ParamInputFileName);

  //   for ( G4int i=1; i<argc; i=i+2 ) 
  //     {
  //       if      ( G4String(argv[i]) == "-m" ) macro = argv[i+1];
  //       else if ( G4String(argv[i]) == "-u" ) session = argv[i+1];
  // #ifdef G4MULTITHREADED
  //       else if ( G4String(argv[i]) == "-t" ) 
  // 	{
  // 	  nThreads = G4UIcommand::ConvertToInt(argv[i+1]);
  // 	}
  // #endif
  //       else 
  // 	{
  // 	  PrintUsage();
  // 	  return 1;
  // 	}
  //     }  

  if(Input_CIN)
    {
      std::string tmpstr;
      while(tmpstr != "HYPHI_MC_BEGINNING_OF_THE_EVENTS")
	{
	  std::cin >> tmpstr;
	}
      int nevents_cin = 0;
      std::cin >> nevents_cin;
      if(nEvent == 0 && nevents_cin == -1)
	{
	  nEvent = INT_MAX;
	  std::cout << "> Number of events is limited by EOF ";
	  std::cout << "(but not more then " << nEvent << ")\n";
	} 
      else if(nevents_cin == -1)
	{
	  std::cout << "> Number of events to simulate: ";
	  std::cout << nEvent << "\n";
	} 
      else if(nEvent == 0 || nEvent > nevents_cin)
	{
	  nEvent = nevents_cin;
	  std::cout << "> Number of events to simulate: ";
	  std::cout << nEvent << "\n";
	} 
      else 
	{
	  std::cout << "> Number of events to simulate: ";
	  std::cout << nEvent << "\n";
	}
    }

  // Choose the Random engine
  //
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  
  // Construct the default run manager
  //

#ifdef G4MULTITHREADED
  G4MTRunManager * runManager = new G4MTRunManager;
  if ( nThreads > 0 ) 
    { 
      runManager->SetNumberOfThreads(nThreads);
    }  
#else
  G4RunManager * runManager = new G4RunManager;
#endif

  // Set mandatory initialization classes
  //
  THypHi_Par* ParameterSet  = Parser.GetParameter();
  
  HypHIFrsDetectorConstruction* detConstruction = new HypHIFrsDetectorConstruction(*ParameterSet);
  runManager->SetUserInitialization(detConstruction);
  
  //G4VModularPhysicsList* physicsList = new FTFP_BERT;
  
  G4VModularPhysicsList* physicsList = new HypHIFrsPhysicsList(*ParameterSet);
  //physicsList->RegisterPhysics(new G4StepLimiterPhysics());
  runManager->SetUserInitialization(physicsList);
    
  HypHIFrsActionInitialization* actionInitialization = new HypHIFrsActionInitialization(detConstruction,*ParameterSet,OutputFileName);
  runManager->SetUserInitialization(actionInitialization);

  // Initialize G4 kernel
  //
  runManager->Initialize();
  
#ifdef G4VIS_USE
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();
#endif

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if ( macro.size() ) 
    {
      // batch mode
      G4String command = "/control/execute ";
      UImanager->ApplyCommand(command+macro);
    }
  else  
    {  
      // interactive mode : define UI session
#ifdef G4UI_USE
      G4UIExecutive* ui = new G4UIExecutive(argc, argv, session);
#ifdef G4VIS_USE
      UImanager->ApplyCommand("/control/execute init_vis.mac"); 
#else
      UImanager->ApplyCommand("/control/execute init.mac"); 
#endif
      if (ui->IsGUI())
	UImanager->ApplyCommand("/control/execute gui.mac");
      ui->SessionStart();
      delete ui;
#endif
    }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !

#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
