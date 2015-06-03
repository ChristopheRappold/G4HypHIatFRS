#ifndef THypHi_SensetiveD_H
#define THypHi_SensetiveD_H 1

#include "G4VSensitiveDetector.hh"
#include "HypHIFrsUTrackerHit.hh"
#include <map>

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class THypHi_SD_UTracker: public G4VSensitiveDetector{
public:
  //
  THypHi_SD_UTracker(const G4String& name, const G4String& nameVolPhysm);
  ~THypHi_SD_UTracker();
  
  G4bool ProcessHits(G4Step*aStep,G4TouchableHistory* rohist);
  virtual void Initialize(G4HCofThisEvent*HCE);
  virtual void EndOfEvent(G4HCofThisEvent*);
  virtual void clear();

  HypHIFrsUTrackerHitsCollection* fHitsCollection;
  G4int fHCID;

  std::map<int,int> mapTrackID_Hits;

};


#endif
