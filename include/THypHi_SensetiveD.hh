#ifndef THypHi_SensetiveD_H
#define THypHi_SensetiveD_H 1

#include "G4VSensitiveDetector.hh"
#include "TClonesArray.h"
#include "THypHi_UTrackerHit.hh"
#include <map>

class THypHi_SD_UTracker: public G4VSensitiveDetector{
public:
  //
  THypHi_SD_UTracker(const G4String& name, const G4String& nameVolPhysm);
  ~THypHi_SD_UTracker();
  
  G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*);
  void Init();
  void EndOfEvent(G4HCofThisEvent*);
  UTrackerHit* AddHit();

  G4String nameDetector;
  TClonesArray* Hits;
  bool AttachedToTree;
  
  std::map<int,int> mapTrackID_Hits;

private :
  static TClonesArray* gHits;

};


#endif
