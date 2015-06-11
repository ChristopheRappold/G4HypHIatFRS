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
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "HypHIFrsStackingAction.hh"

#include "G4VProcess.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"

#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIFrsStackingAction::HypHIFrsStackingAction()
  : G4UserStackingAction()

{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HypHIFrsStackingAction::~HypHIFrsStackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
HypHIFrsStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
  if(aTrack->GetDefinition() == G4Lambda::Definition())
  { 
    // G4cout<<" Stacking ClassifyNewTrack:"<<G4endl;
    // G4cout<<"Find Lambda :"<<aTrack->GetTrackID()<<G4endl;
    G4int mother_id = aTrack->GetTrackID();
    const G4DynamicParticle* tempParticle = aTrack->GetDynamicParticle(); 
    tempParticle->DumpInfo();
    // G4cout<<" Vtx Position"<<aTrack->GetPosition()<<G4endl;
    // G4cout<<" Time :"<<aTrack->GetProperTime()/ns<<" "<<" "<<aTrack->GetLocalTime()/ns<<" "<<aTrack->GetGlobalTime()/ns<<G4endl;
    
    std::map<G4int,Daugthers_Info>::const_iterator it_mother = mother_daugthersInfo.find(mother_id);
    if(it_mother==mother_daugthersInfo.end())
      {
	Daugthers_Info newInfo;
	mother_daugthersInfo.insert(std::pair<G4int,Daugthers_Info>(mother_id,newInfo));
      }
  }
  
  if(aTrack->GetParentID()>0)
    {
      //G4cout<<"Process :"<<aTrack->GetCreatorProcess()->GetProcessName()<<G4endl;
      if(aTrack->GetCreatorProcess()->GetProcessName()=="Decay")
	{
	  std::map<G4int,Daugthers_Info>::iterator it_mother = mother_daugthersInfo.find(aTrack->GetParentID());
	  
	  if(it_mother!=mother_daugthersInfo.end())
	    { // particle is secondary
	      //G4cout<<"Stacking: "<<aTrack->GetCreatorProcess()->GetProcessName()<<G4endl;
	      const G4DynamicParticle* tempParticle = aTrack->GetDynamicParticle(); 
	      tempParticle->DumpInfo();
	      //G4cout<<" Vtx Position"<<aTrack->GetPosition()<<G4endl;
	      //G4cout<<" Time :"<<aTrack->GetProperTime()/ns<<" "<<" "<<aTrack->GetLocalTime()/ns<<" "<<aTrack->GetGlobalTime()/ns<<G4endl;
	      if(it_mother->second.mass_daughters.size()==0)
		{
		  it_mother->second.secondary_vertex = aTrack->GetPosition();
		  it_mother->second.decaytime = aTrack->GetGlobalTime();
		  it_mother->second.mom_daughters.push_back(aTrack->GetMomentum());
		  it_mother->second.mass_daughters.push_back(tempParticle->GetMass());
		  it_mother->second.name_daughters.push_back(tempParticle->GetParticleDefinition()->GetParticleName());
		  it_mother->second.charge_daughters.push_back(tempParticle->GetCharge());
		}
	      else
		{
		  if(it_mother->second.secondary_vertex != aTrack->GetPosition())
		    {
		      G4cout<<"E > Secondary Vertex position different !"<<it_mother->second.secondary_vertex<<" "<<aTrack->GetPosition()<<G4endl;
		    }
		  
		  it_mother->second.mom_daughters.push_back(aTrack->GetMomentum());
		  it_mother->second.mass_daughters.push_back(tempParticle->GetMass());
		  it_mother->second.name_daughters.push_back(tempParticle->GetParticleDefinition()->GetParticleName());
		  it_mother->second.charge_daughters.push_back(tempParticle->GetCharge());

		}
	    }
	}
    }
  //G4cout<<" ---- "<<G4endl;

  return fUrgent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HypHIFrsStackingAction::NewStage()
{
  // G4cout << "Number of Scintillation photons produced in this event : "
  //        << fScintillationCounter << G4endl;
  // G4cout << "Number of Cerenkov photons produced in this event : "
  //        << fCerenkovCounter << G4endl;

  G4cout<<" Decay in the event :"<<G4endl;
  for(const auto& elem : mother_daugthersInfo)
    {
      elem.second.Print();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HypHIFrsStackingAction::PrepareNewEvent()
{
  mother_daugthersInfo.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool HypHIFrsStackingAction::Get_MotherInfo(G4int id) const
{
  std::map<G4int,Daugthers_Info>::const_iterator it_motherOut = mother_daugthersInfo.find(id);

  return it_motherOut != mother_daugthersInfo.end();
}

const Daugthers_Info HypHIFrsStackingAction::Get_DaugthersInfo(G4int id) const
{

  std::map<G4int,Daugthers_Info>::const_iterator it_motherOut = mother_daugthersInfo.find(id);
  if(it_motherOut!=mother_daugthersInfo.end())
    {
      return it_motherOut->second;
    }
  else
    {
      G4cout<<"E> Stack Info no daugther info for this mother ID "<<id<<G4endl;
    }


  Daugthers_Info temp;
  return temp;
}
