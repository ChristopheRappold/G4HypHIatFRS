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

#ifndef HypHIFrsStackingAction_H
#define HypHIFrsStackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"
#include "G4ThreeVector.hh"
#include "G4String.hh"

#include <vector>
#include <unordered_map>
#include <tuple>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

struct Daugthers_Info
{

  G4ThreeVector secondary_vertex;
  G4double decaytime;
  std::vector<G4ThreeVector> mom_daughters;
  std::vector<G4double> mass_daughters;
  std::vector<G4double> charge_daughters;
  std::vector<G4String> name_daughters;
  std::vector<G4int> trackID_daughters;

  void Print() const
  {
    G4cout<<" Daugther :"<<G4endl;
    G4cout<<" Secondary vertex :"<<secondary_vertex<<G4endl;

    for(unsigned int i=0; i< name_daughters.size();++i)
      {
	G4cout<<" name :"<<name_daughters[i]<<G4endl;
	G4cout<<"  '--> mom"<<mom_daughters[i]<<G4endl;
      }
  }
};

class HypHIFrsStackingAction : public G4UserStackingAction
{
public:
  HypHIFrsStackingAction();
  virtual ~HypHIFrsStackingAction();

public:
  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
  virtual void NewStage();
  virtual void PrepareNewEvent();

  bool Get_MotherInfo(G4int ) const;
  const Daugthers_Info Get_DaugthersInfo(G4int ) const;
private:
  
  std::unordered_map<G4int,Daugthers_Info> mother_daugthersInfo;
  std::unordered_map<G4int,std::vector<std::tuple<double,double> > > optic_lines;
  

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
