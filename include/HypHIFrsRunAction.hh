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
// $Id: HypHIFrsRunAction.hh 74265 2013-10-02 14:41:20Z gcosmo $
// 
/// \file HypHIFrsRunAction.hh
/// \brief Definition of the HypHIFrsRunAction class

#ifndef HypHIFrsRunAction_h
#define HypHIFrsRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "THypHi_Par.hh"

class G4Run;

/// Run action class
///
/// It accumulates statistic and computes dispersion of the energy deposit 
/// and track lengths of charged particles with use of analysis tools:
/// H1D histograms are created in BeginOfRunAction() for the following 
/// physics quantities:
/// - Edep in absorber
/// - Edep in gap
/// - Track length in absorber
/// - Track length in gap
/// The same values are also saved in the ntuple.
/// The histograms and ntuple are saved in the output file in a format
/// accoring to a selected technology in HypHIFrsAnalysis.hh.
///
/// In EndOfRunAction(), the accumulated statistic and computed 
/// dispersion is printed.
///

class HypHIFrsRunAction : public G4UserRunAction
{
public:
  HypHIFrsRunAction(const G4String& name, const std::vector<G4String>& nameD, const THypHi_Par&);
  virtual ~HypHIFrsRunAction();
  
  virtual void BeginOfRunAction(const G4Run*);
  virtual void   EndOfRunAction(const G4Run*);
  
  virtual G4Run* GenerateRun();


  // void Close();
  // void Fill() const;
private :
  const G4String& OutputFileName;
  const std::vector<G4String>& NameDetectorsSD;
  const THypHi_Par& Par;

  // TFile* OutputFile;
  // TTree* OutTree;

  // TH1F* h1;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

