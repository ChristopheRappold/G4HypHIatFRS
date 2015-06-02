#include "HypHIFrsUTrackerHit.hh"

#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

G4ThreadLocal G4Allocator<HypHIFrsUTrackerHit>* HypHIFrsUTrackerHitAllocator;


HypHIFrsUTrackerHit::HypHIFrsUTrackerHit():TrackID(-1), 
			   HitPosX(-9999.) , HitPosY(-9999.) , HitPosZ(-9999.) , 
			   ExitPosX(-9999.), ExitPosY(-9999.), ExitPosZ(-9999.),
			   MomX(-9999.)    , MomY(-9999.)    , MomZ(-9999.)    ,
			   Energy(-9999.), Time(-9999.), 
			   Pname(0),LayerID(-1)
			   
{}

HypHIFrsUTrackerHit::HypHIFrsUTrackerHit(G4int z):TrackID(-1), 
				  HitPosX(-9999.) , HitPosY(-9999.) , HitPosZ(-9999.) , 
				  ExitPosX(-9999.), ExitPosY(-9999.), ExitPosZ(-9999.),
				  MomX(-9999.)    , MomY(-9999.)    , MomZ(-9999.)    ,
				  Energy(-9999.), Time(-9999.), 
				  Pname(0),LayerID(z)
			   
{}

HypHIFrsUTrackerHit::HypHIFrsUTrackerHit(const HypHIFrsUTrackerHit& hit):G4VHit()
{
  TrackID = hit.TrackID; 
  HitPosX = hit.HitPosX; 
  HitPosY = hit.HitPosY; 
  HitPosZ = hit.HitPosZ; 
  ExitPosX = hit.ExitPosX; 
  ExitPosY = hit.ExitPosY; 
  ExitPosZ = hit.ExitPosZ;
  MomX = hit.MomX;
  MomY = hit.MomY; 
  MomZ = hit.MomZ;
  Energy = hit.Energy;
  Time = hit.Time; 
  Pname = hit.Pname;
  LayerID = hit.LayerID;
  
}

const HypHIFrsUTrackerHit& HypHIFrsUTrackerHit::operator=(const HypHIFrsUTrackerHit& hit)
{
  TrackID = hit.TrackID; 
  HitPosX = hit.HitPosX; 
  HitPosY = hit.HitPosY; 
  HitPosZ = hit.HitPosZ; 
  ExitPosX = hit.ExitPosX; 
  ExitPosY = hit.ExitPosY; 
  ExitPosZ = hit.ExitPosZ;
  MomX = hit.MomX;
  MomY = hit.MomY; 
  MomZ = hit.MomZ;
  Energy = hit.Energy;
  Time = hit.Time; 
  Pname = hit.Pname;
  LayerID = hit.LayerID;
  
  return *this;
}

int HypHIFrsUTrackerHit::operator==(const HypHIFrsUTrackerHit& hit)
{
  return LayerID==hit.LayerID && TrackID==hit.TrackID;
}

void HypHIFrsUTrackerHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
    {
      G4Circle circle(G4Point3D(HitPosX,HitPosY,HitPosZ));
      circle.SetScreenSize(2);
      circle.SetFillStyle(G4Circle::filled);
      G4Colour colour(1.,1.,0.);
      G4VisAttributes attribs(colour);
      circle.SetVisAttributes(attribs);
      pVVisManager->Draw(circle);
    }
}



HypHIFrsUTrackerHit::~HypHIFrsUTrackerHit() {}

void HypHIFrsUTrackerHit::Print()
{
  std::cout<<"The THypHIFrsUTrackerHit #" <<TrackID<<std::endl;
  std::cout<<"Particle name:"<<Pname<<" Edep:"<<Energy<<" Time:"<<Time<<std::endl;
  std::cout<<"Position :"<<HitPosX<<" "<<HitPosY<<" "<<HitPosZ<<std::endl;
  std::cout<<"Exit Position :"<<ExitPosX<<" "<<ExitPosY<<" "<<ExitPosZ<<std::endl;
  std::cout<<"Momentum :"<<MomX<<" "<<MomY<<" "<<MomZ<<std::endl;
} 
