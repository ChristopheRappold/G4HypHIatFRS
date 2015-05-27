#include "THypHi_UTrackerHit.hh"
#include <iostream>

UTrackerHit::UTrackerHit():TrackID(-1), 
			   HitPosX(-9999.) , HitPosY(-9999.) , HitPosZ(-9999.) , 
			   ExitPosX(-9999.), ExitPosY(-9999.), ExitPosZ(-9999.),
			   MomX(-9999.)    , MomY(-9999.)    , MomZ(-9999.)    ,
			   Energy(-9999.), Time(-9999.), 
			   Pname(0)
			   
{}

UTrackerHit::~UTrackerHit() {}

void UTrackerHit::Print(const Option_t*) const
{
  std::cout<<"The TUTrackerHit #" <<TrackID<<std::endl;
  std::cout<<"Particle name:"<<Pname<<" Edep:"<<Energy<<" Time:"<<Time<<std::endl;
  std::cout<<"Position :"<<HitPosX<<" "<<HitPosY<<" "<<HitPosZ<<std::endl;
  std::cout<<"Exit Position :"<<ExitPosX<<" "<<ExitPosY<<" "<<ExitPosZ<<std::endl;
  std::cout<<"Momentum :"<<MomX<<" "<<MomY<<" "<<MomZ<<std::endl;
} 
