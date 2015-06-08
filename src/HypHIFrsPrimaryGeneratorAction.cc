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
// $Id: HypHIFrsPrimaryGeneratorAction.cc 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file HypHIFrsPrimaryGeneratorAction.cc
/// \brief Implementation of the HypHIFrsPrimaryGeneratorAction class

#include "HypHIFrsPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
// #include "G4LogicalVolumeStore.hh"
// #include "G4LogicalVolume.hh"

#include "G4PhysicalVolumeStore.hh"
#include "G4VPhysicalVolume.hh"

#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"

#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIFrsPrimaryGeneratorAction::HypHIFrsPrimaryGeneratorAction(const THypHi_Par& _par, bool In) : G4VUserPrimaryGeneratorAction(), fParticleGun(0),Par(_par),InputCIN(In),RandomizePos(false),RandomizeEnergy(false),RandomizeDirection(false)
{
  G4int nofParticles = 1;

  fParticleGun = new G4ParticleGun(nofParticles);

  // default particle kinematic
  //
  if(In==false)
    ConstParticle = GetParticle(Par.Get_Beam_Type());
  else
    ConstParticle = nullptr;
  
  fParticleGun->SetParticleDefinition(ConstParticle);
  
  //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  //fParticleGun->SetParticleEnergy(50.*MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIFrsPrimaryGeneratorAction::~HypHIFrsPrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HypHIFrsPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // This function is called at the begining of event

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get world volume
  // from G4LogicalVolumeStore
  //
  //G4double worldZHalfLength = 0;
  //G4LogicalVolume* worlLV = G4LogicalVolumeStore::GetInstance()->GetVolume("Target");

  G4double energy;

  G4double pos_x = Par.Get_Geometry_TargetPosX();
  G4double pos_y = Par.Get_Geometry_TargetPosY();
  G4double pos_z = Par.Get_Geometry_TargetPosZ();
  G4double sigma = Par.Get_Beam_SpotSizeSigma();

  bool not_acc_position = true;
  G4double ofpos_x,ofpos_y,ofpos_z;
  
  while(not_acc_position)
    {
      G4double r0;
      //r0 = s*std::sqrt(G4UniformRand()); // Uniformly distributed
      
      r0 = sigma*std::sqrt(-std::log(G4UniformRand())); // Gaus
      G4double phi = 2.0*CLHEP::pi*G4UniformRand();
      ofpos_x = r0*cos(phi);
      ofpos_y = r0*sin(phi);
      ofpos_z = Par.Get_Geometry_TargetThickness() * (0.5 - G4UniformRand());

      if(std::abs(ofpos_x)<=Par.Get_Geometry_TargetLength()/2.0 && std::abs(ofpos_y)<=Par.Get_Geometry_TargetHeight()/2.0)
	not_acc_position = false;

      //  std::cout<<"r0= "<<r0<<" "<<ofpos_x<<" "<<ofpos_y<<" "<<ofpos_z<<" "<< sqrt(ofpos_x*ofpos_x+ofpos_y*ofpos_y+ofpos_z*ofpos_z)<<std::endl;

    }

  if(RandomizePos)
    {
      pos_x += ofpos_x;
      pos_y += ofpos_y;
      pos_z += ofpos_z;
    }

  if(InputCIN)
    { // CIN input
      Int_t Multiplisity = 0;
      //	THypHi_Communicator::n_current_event++;
      //std::cout << "--------------" << THypHi_Communicator::n_current_event << std::endl; 
      std::cin >> Multiplisity;
      //std::cout << "-------" << Multiplisity << std::endl;
      if(std::cin.eof() || std::cin.fail())
	{
	  std::cout << "!> End of the file is reached!!!\n";
	  G4RunManager::GetRunManager()->AbortRun(true);
	  return;
	} 
      else if(Multiplisity <= 0)
	{
	  std::cout << "!> Wrong multiplisity ";
	  std::cout << Multiplisity << "\n";
	  G4RunManager::GetRunManager()->AbortRun(true);
	  return;
	}
      std::string particlename;
      G4ParticleDefinition* particle;
      G4double phi_ofset = 2.0*CLHEP::pi*(0.5-G4UniformRand());
      //int pnum=0;
      for(int i=0;i<Multiplisity;i++)
	{
	  std::cin >> particlename;
	  
	  //	    std::cout<<"-I- Particle name in Generator ===>  "<<particlename<<std::endl;
	  
	  particle = GetParticle(particlename);
	  //
	  G4String particleName_temp = particle->GetParticleName();
	  //	    std::cout<<"come here "<<particleName_temp<<std::endl;
	  
	  std::string tstr;
	  bool accept = true;
	  //    	    if(particleName_temp!="L")
	  //    	      accept = false;
	  
	  if(particleName_temp=="gamma")
	    accept = false;
	  
	  // 	    if(particleName_temp=="sigma0"||
	  // 	       particleName_temp=="sigma+"||
	  // 	       particleName_temp=="sigma-")
	  // 	      continue;
	  
	  //
	  // 	    if(particleName_temp!="proton")accept=false;
	  //  	    if(particleName_temp=="proton")
	  //  	      {
	  //  		pnum++;
	  //  	      }
	  //  	    if(pnum>1)accept=false;
	  
	  G4double Px,Py,Pz;
	  std::cin >> energy;
	  if(std::cin.fail())
	    {
	      std::cin.clear();
	      std::cin >> tstr;
	      std::cout << "Energy Faile: " << tstr << "\n";
	      accept = false;
	    }
	  std::cin >> Px;
	  if(std::cin.fail())
	    {
	      std::cin.clear();
	      std::cin >> tstr;
	      std::cout << "Px Faile: " << tstr << "\n";
	      accept = false;
	    }
	  std::cin >> Py;
	  if(std::cin.fail())
	    {
	      std::cin.clear();
	      std::cin >> tstr;
	      std::cout << "Py Faile: " << tstr << "\n";
	      accept = false;
	    }
	  std::cin >> Pz;
	  if(std::cin.fail())
	    {
	      std::cin.clear();
	      std::cin >> tstr;
	      std::cout << "Pz Faile: " << tstr << "\n";
	      accept = false;
	    }
	    //
	  if(accept && energy > 0)
	    {
	      fParticleGun->SetParticleDefinition(particle);
	      // direction
	      G4ThreeVector mom(Px,Py,Pz);
	      // 		std::cout<<energy<<" "<<Px<<" "<<Py<<" "<<Pz<<std::endl;
	      // 		std::cout<<mom.x()<<" "<<mom.y()<<" "<<mom.z()<<std::endl;
	      
	      mom.setPhi(mom.phi()+phi_ofset); //open for rotation of repeated mom seed
	      fParticleGun->SetParticleMomentumDirection(mom);
	      //
	      fParticleGun->SetParticleEnergy(energy);
	      fParticleGun->SetParticlePosition(G4ThreeVector(pos_x,pos_y,pos_z));

	      fParticleGun->GeneratePrimaryVertex(anEvent);
	      //
	      // Event->BeamNames.push_back(particle->GetParticleName());
	      // Event->BeamMasses.push_back(particle->GetPDGMass());
	      // Event->BeamCharges.push_back(particle->GetPDGCharge());
	      // Event->BeamMomentums_X.push_back(mom.x());//Px);
	      // Event->BeamMomentums_Y.push_back(mom.y());//Py);
	      // Event->BeamMomentums_Z.push_back(mom.z());//Pz);
	    }
	}
    }
  else
    {

      energy = Par.Get_Beam_KineticEnergy();

      if(RandomizeEnergy)
	energy += 1000*std::sqrt(-std::log(G4UniformRand()-0.5)); // Gaus
      
      fParticleGun->SetParticleDefinition(ConstParticle);

      if(RandomizeDirection)
	{
	  //         G4double rr00;
	  // 	rr0 = 100*std::sqrt(-std::log(G4UniformRand())); // Gaus
	  // 	G4double phi = 2.0*pi*G4UniformRand();
	  // 	ofpos_x = r0*cos(phi);
	  // 	ofpos_y = r0*sin(phi);
	  // 	ofpos_z = Par.Get_Geometry_TargetThickness() *
	  // 		(0.5 - G4UniformRand());
	  double xdir = Par.Get_Beam_MomentumDirectionX();
	  double ydir = Par.Get_Beam_MomentumDirectionY();
	  double zdir = Par.Get_Beam_MomentumDirectionZ();
	  
	  xdir +=0.1*std::sqrt(-std::log(G4UniformRand()-0.5));
	  ydir +=0.1*std::sqrt(-std::log(G4UniformRand()-0.5));
	  zdir = sqrt(1.0-ydir*ydir-xdir*xdir);
	  std::cout<<xdir<<" "<<ydir<<" "<<zdir<<std::endl;

	  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(xdir,ydir,zdir));
	}
      else
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(Par.Get_Beam_MomentumDirectionX(), Par.Get_Beam_MomentumDirectionY(), Par.Get_Beam_MomentumDirectionZ()));

	fParticleGun->SetParticleEnergy(energy);
	//
	fParticleGun->SetParticlePosition(G4ThreeVector(pos_x,pos_y,pos_z));
	//	fParticleGun->SetParticlePosition(G4ThreeVector(0,0,0));
	fParticleGun->GeneratePrimaryVertex(anEvent);
	
	//
	// Event->BeamNames.push_back(ConstParticle->GetParticleName());
	// Event->BeamMasses.push_back(ConstParticle->GetPDGMass());
	// Event->BeamCharges.push_back(ConstParticle->GetPDGCharge());
	// //
	// G4double momentum = std::sqrt(energy*(energy+2.0*ConstParticle->GetPDGMass()));
	// Event->BeamMomentums_X.push_back(0);
	// Event->BeamMomentums_Y.push_back(0);
	// Event->BeamMomentums_Z.push_back(momentum);
    }



	
  //G4VPhysicalVolume* tarPV = G4PhysicalVolumeStore::GetInstance()->GetVolume("Target");


  // for(auto& elem : *G4PhysicalVolumeStore::GetInstance() )
  //   {
  //     G4cout<<" PhysicalVol "<<elem->GetName()<<G4endl;
  //   }
  // G4cout<<" size "<<G4PhysicalVolumeStore::GetInstance()->size()<<G4endl;

  //G4Box* worldBox = 0;
  // if ( worlLV) 
  //   worldBox = dynamic_cast< G4Box*>(worlLV->GetSolid()); 
 
  // if ( worldBox ) 
  //   {
  //     //worldZHalfLength = worldBox->GetZHalfLength();  
  //     pos[0] = tarPV->GetTranslation().getX();
  //     pos[1] = tarPV->GetTranslation().getY();
  //     pos[2] = tarPV->GetTranslation().getZ();

  //   }
  // else  
  //   {
  //     G4ExceptionDescription msg;
  //     msg << "World volume of box not found." << G4endl;
  //     msg << "Perhaps you have changed geometry." << G4endl;
  //     msg << "The gun will be place in the center.";
  //     G4Exception("HypHIFrsPrimaryGeneratorAction::GeneratePrimaries()", "MyCode0002", JustWarning, msg);
  //   } 
  return;
  // Set gun position
  //fParticleGun->SetParticlePosition(G4ThreeVector(2.5*cm,0.,0.));

  //fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



G4ParticleDefinition* HypHIFrsPrimaryGeneratorAction::GetParticle(const G4String& particleName)
{

  G4ParticleTable* pTable = G4ParticleTable::GetParticleTable();

  G4IonTable* pTableIon = G4IonTable::GetIonTable();
  //pTableIon->CreateAllIon();
//     G4ParticleDefinition* particle = pTable->FindParticle(particleName);
//     if(particle) return particle;

  G4ParticleDefinition* particle;// = pTable->FindParticle(particleName);

  G4int Apos = particleName.rfind("A");
  G4int Zpos = particleName.rfind("Z");
  G4int Epos = particleName.rfind("E");
  G4int Lpos = particleName.rfind("L");
  
    
  if(Zpos!=(G4int)G4String::npos)
    {
      //	std::cout<<"zpos >0 "<<particleName<<std::endl;
      if(particleName=="Z2A4")
	{
	  particle = pTable->FindParticle("alpha");
	  if(particle) return particle;
	}
      else if(particleName=="Z2A3")
	{
	  particle = pTable->FindParticle("He3");
	  //particle = pTable->FindParticle("alpha");
	  if(particle) return particle;
	}
      else if(particleName=="Z1A2")
	{
	  //	    std::cout<<" come to deuteron "<<std::endl;
	  particle = pTable->FindParticle("deuteron");
	  if(particle) return particle;
	}
      else if(particleName=="Z1A3")
	{
	  particle = pTable->FindParticle("triton");
	  if(particle) return particle;
	}
      else
	{
	  //particle = pTable->FindParticle("gamma");

	  
	  //
	  if(Apos==(G4int)G4String::npos || Zpos==(G4int)G4String::npos)
	    {
	      std::cout << "!> Fatal error!\n";
	      std::cout << "!>    Particle: " << particleName;
	      std::cout << " is not found! (Primary Gen)\n";
	      std::exit(1);
	    }
	  if(Apos<Zpos)
	    {
	      std::cout << "!> Fatal error!\n";
	      std::cout << "!>    Wrong ion format! should be like ";
	      std::cout << " Z1A20E5.11\n";
	      std::exit(1);
	    }
	    //
	  G4double E = 0;
	  G4int endl = particleName.size();
	  if(Epos!=(G4int)G4String::npos)
	    {
	      G4String Estr = particleName.substr(Epos+1,endl-Epos-1);
	      E = std::atof(Estr.c_str());
	      endl = Epos;
	    }
	  //
	  G4String Zstr = particleName.substr(Zpos+1,Apos-Zpos-1);
	  G4String Astr = particleName.substr(Apos+1,endl-Apos-1);
	  G4int Z = std::atoi(Zstr.c_str());
	  G4int A = std::atoi(Astr.c_str());
	  //printf("A = %i; Z = %i; E = %f\n",A,Z,E);
	  //
	  particle = pTableIon->GetIon(Z,A,E);
	  if(!particle)
	    {
	      std::cout << "!> Fatal error!\n";
	      std::cout << "!>    Cannot create the ion ";
	      std::cout << particleName << "\n";
	      std::exit(1);
	    }
	    
	  //	    std::cout<<" come to something "<<std::endl;
	  if(particle) return particle;
	}
    }
  else if(Lpos!=(G4int)G4String::npos)
    {
      if(particleName=="Lambda")
	{
	  particle = pTable->FindParticle(particleName);
	  if(particle) return particle;
	}
      else if(particleName=="H3L")
	{
	  particle = pTableIon->GetIon(1,3,0.,1);
	  if(particle)
	    return particle;
	  else
	    {
	      std::cout << "!> Fatal error!\n";
	      std::cout << "!>    Cannot create the ion ";
	      std::cout << particleName << "\n";
	      std::exit(1);
	    }
	}
      else if(particleName=="H4L")
	{
	  particle = pTableIon->GetIon(1,4,0.,1);
	  if(particle)
	    return particle;
	  else
	    {
	      std::cout << "!> Fatal error!\n";
	      std::cout << "!>    Cannot create the ion ";
	      std::cout << particleName << "\n";
	      std::exit(1);
	    }
	}
      else
	{
	  std::cout << "!> Fatal error!\n";
	  std::cout << "!>    Cannot create the ion ";
	  std::cout << particleName << "\n";
	  std::exit(1);
	}
    }
  else
    {
      particle = pTable->FindParticle(particleName);
      if(particle) return particle;
    }
  

    /*
    //
    if(Apos==(G4int)G4String::npos || Zpos==(G4int)G4String::npos){
	std::cout << "!> Fatal error!\n";
	std::cout << "!>    Particle: " << particleName;
	std::cout << " is not found! (Primary Gen)\n";
	std::exit(1);
    }
    if(Apos<Zpos){
	std::cout << "!> Fatal error!\n";
	std::cout << "!>    Wrong ion format! should be like ";
	std::cout << " Z1A20E5.11\n";
	std::exit(1);
    }
    //
    G4double E = 0;
    G4int endl = particleName.size();
    if(Epos!=(G4int)G4String::npos){
	G4String Estr = particleName.substr(Epos+1,endl-Epos-1);
	E = std::atof(Estr.c_str());
	endl = Epos;
    }
    //
    G4String Zstr = particleName.substr(Zpos+1,Apos-Zpos-1);
    G4String Astr = particleName.substr(Apos+1,endl-Apos-1);
    G4int Z = std::atoi(Zstr.c_str());
    G4int A = std::atoi(Astr.c_str());
    //printf("A = %i; Z = %i; E = %f\n",A,Z,E);
    //
    particle = pTable->GetIon(Z,A,E);
    if(!particle){
	std::cout << "!> Fatal error!\n";
	std::cout << "!>    Cannot create the ion ";
	std::cout << particleName << "\n";
	std::exit(1);
    }
    */
  return particle;
}
