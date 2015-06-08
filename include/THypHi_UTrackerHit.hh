#ifndef HYPHI_UTRACKER_HIT_H
#define HYPHI_UTRACKER_HIT_H

#include "TObject.h"
#include <string>

class UTrackerHit : public TObject
{
  public:
  UTrackerHit();
  ~UTrackerHit();

  virtual void Print(const Option_t* = "") const;
  
  Int_t      TrackID;   ///< Track Id

  Double32_t HitPosX;
  Double32_t HitPosY;
  Double32_t HitPosZ;

  Double32_t ExitPosX; 
  Double32_t ExitPosY; 
  Double32_t ExitPosZ; 

  Double32_t MomX;   
  Double32_t MomY;   
  Double32_t MomZ;   
  Double32_t Mass;   

  Double32_t Energy; 
  Double32_t Time;   

  std::string Pname;
    
  ClassDef(UTrackerHit,1) //Ex02TrackerHit  
};

#endif // UTRACKER_HIT_H


