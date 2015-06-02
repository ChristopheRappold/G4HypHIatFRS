#include "THypHi_SensetiveD.hh"
#include "G4ParticleTypes.hh"
#include "G4Step.hh"

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

#include "G4VTouchable.hh"
#include "G4VSolid.hh"
#include "G4Material.hh"


THypHi_SD_UTracker::THypHi_SD_UTracker(const G4String& name, const G4String& nameVolPhys):  G4VSensitiveDetector(name),fHitsCollection(nullptr),fHCID(-1)
{ 
  collectionName.insert("UTrackerColl");
}

THypHi_SD_UTracker::~THypHi_SD_UTracker()
{
  
}

void THypHi_SD_UTracker::Initialize(G4HCofThisEvent* hce)
{
  fHitsCollection = new HypHIFrsUTrackerHitsCollection(SensitiveDetectorName,collectionName[0]);
  if ( fHCID<0 )
    fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
  
  hce->AddHitsCollection(fHCID,fHitsCollection);
}

// void THypHi_SD_UTracker::EndOfEvent(G4HCofThisEvent*)
// {
//   Hits->Clear("C");
//   mapTrackID_Hits.clear();
// }

G4bool THypHi_SD_UTracker::ProcessHits(G4Step*aStep, G4TouchableHistory*)
{
  
  G4double energ_depos = aStep->GetTotalEnergyDeposit();
  //
  G4cout<<" Current SD :"<<nameDetector<<" "<<energ_depos<<G4endl;
  if(energ_depos < 1e-4) 
    return true;
  
  G4String PhysName (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName());
  G4cout<<" ->"<<PhysName<<G4endl;
  
  if(PhysName!=SensitiveDetectorName)
    return true;

  int IdHit = -1;
  Int_t CurrentTrack = aStep->GetTrack()->GetTrackID();
  //for(int i=(int)Event->id.size()-1;i>-1;i--)
  
  G4cout<<" --> Track#"<<CurrentTrack<<G4endl;

  std::map<int,int>::const_iterator it_track = mapTrackID_Hits.find(CurrentTrack);

  if(it_track != mapTrackID_Hits.end())
    IdHit = it_track->second;

  G4cout<<" --> IdHit:"<<IdHit;

  if(IdHit==-1)
    {
      G4cout<<" NewHit !"<<G4endl;
      IdHit = fHitsCollection->GetSize();
      HypHIFrsUTrackerHit* newHit = HypHIFrsUTrackerHit(fHCID);

      newHit->Pname = aStep->GetTrack()->GetDefinition()->GetPDGEncoding();
      newHit->TrackID = aStep->GetTrack()->GetTrackID();
      newHit->Energy = energ_depos;
      newHit->Time = aStep->GetPreStepPoint()->GetGlobalTime();
      newHit->HitPosX = aStep->GetTrack()->GetPosition().x();
      newHit->HitPosY = aStep->GetTrack()->GetPosition().y();
      newHit->HitPosZ = aStep->GetTrack()->GetPosition().z();
      newHit->ExitPosX = aStep->GetTrack()->GetPosition().x();
      newHit->ExitPosY = aStep->GetTrack()->GetPosition().y();
      newHit->ExitPosZ = aStep->GetTrack()->GetPosition().z();
      newHit->MomX = aStep->GetTrack()->GetMomentum().x();
      newHit->MomY = aStep->GetTrack()->GetMomentum().y();
      newHit->MomZ = aStep->GetTrack()->GetMomentum().z();

      mapTrackID_Hits.insert(std::pair<int,int>(CurrentTrack,IdHit));

      fHitsCollection->insert(newHits);
    }
  else
    {
      G4cout<<" Hit#"<<IdHit<<G4endl;
      HypHIFrsUTrackerHit* CurrentHit =dynamic_cast<HypHIFrsUTrackerHit*>(Hits->GetHit(IdHit));
      
      CurrentHit->Energy += energ_depos;
      CurrentHit->ExitPosX = aStep->GetTrack()->GetPosition().x();
      CurrentHit->ExitPosY = aStep->GetTrack()->GetPosition().y();
      CurrentHit->ExitPosZ = aStep->GetTrack()->GetPosition().z();
    }
  //
  return true;
}
