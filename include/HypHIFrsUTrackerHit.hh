#ifndef HYPHIFRSUTRACKER_HIT_H
#define HYPHIFRSUTRACKER_HIT_H

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

//#include <string>

class HypHIFrsUTrackerHit : public G4VHit
{
  public:
  HypHIFrsUTrackerHit();
  HypHIFrsUTrackerHit(G4int z);
  HypHIFrsUTrackerHit(const HypHIFrsUTrackerHit& hit);
  ~HypHIFrsUTrackerHit();

  const HypHIFrsUTrackerHit& operator=(const HypHIFrsUTrackerHit& right);
  int operator==(const HypHIFrsUTrackerHit &right) const;

  inline void *operator new(size_t);
  inline void operator delete(void *aHit);

  virtual void Draw();
  // virtual const std::map<G4String,G4AttDef>* GetAttDefs() const;
  // virtual std::vector<G4AttValue>* CreateAttValues() const;
  virtual void Print();

  
  G4int TrackID;   ///< Track Id

  G4double HitPosX;
  G4double HitPosY;
  G4double HitPosZ;

  G4double ExitPosX; 
  G4double ExitPosY; 
  G4double ExitPosZ; 

  G4double MomX;   
  G4double MomY;   
  G4double MomZ;   

  G4double Energy; 
  G4double Time;   

  G4int Pname;

  G4int LayerID; 

};
typedef G4THitsCollection<HypHIFrsUTrackerHit> HypHIFrsUTrackerHitsCollection;

extern G4ThreadLocal G4Allocator<HypHIFrsUTrackerHit>* HypHIFrsUTrackerHitAllocator;

inline void* HypHIFrsUTrackerHit::operator new(size_t)
{
    if (!HypHIFrsUTrackerHitAllocator)
        HypHIFrsUTrackerHitAllocator = new G4Allocator<HypHIFrsUTrackerHit>;
    return (void*)HypHIFrsUTrackerHitAllocator->MallocSingle();
}

inline void HypHIFrsUTrackerHit::operator delete(void* aHit)
{
    HypHIFrsUTrackerHitAllocator->FreeSingle((HypHIFrsUTrackerHit*) aHit);
}

#endif // UTRACKER_HIT_H


