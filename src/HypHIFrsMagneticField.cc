#include "HypHIFrsMagneticField.hh"
#include "G4FieldManager.hh"
#include "G4SystemOfUnits.hh"


HypHIFrsMagneticField::HypHIFrsMagneticField(const G4String& name):namefield(name),factor(1.),normalized(true)
{
}

HypHIFrsMagneticField::~HypHIFrsMagneticField()
{
  if(FieldMap)
    {
      delete FieldMap;
      FieldMap= 0;
    }
}

void HypHIFrsMagneticField::InitField(double fac,bool secondMagnet,double SBz,bool Solenoid)
{
  
  if(Solenoid==false)
    {
      FieldMap = new FrsSksHypFieldMapFull(namefield);

      //dynamic_cast<FrsSksHypFieldMapFull*>(FieldMap)->SetPosition((1894.014-100)*0.1,0,(414.+40+20+400.+419.89)*0.1,90.*TMath::Pi()/180.,(90.+25+10)*TMath::Pi()/180.);//->SetPosition(0.,0.,0.,0.); // Geometry already in the magnet center

      dynamic_cast<FrsSksHypFieldMapFull*>(FieldMap)->SetPositionFromGeoManager("TMsystem");
      dynamic_cast<FrsSksHypFieldMapFull*>(FieldMap)->Init();
      if(secondMagnet)
	{
	  dynamic_cast<FrsSksHypFieldMapFull*>(FieldMap)->SetPositionSecondFromGeoManager("TMsystem3","SecondMag");
	  dynamic_cast<FrsSksHypFieldMapFull*>(FieldMap)->InitSecond(0.,0.,SBz); // kG
	}
      dynamic_cast<FrsSksHypFieldMapFull*>(FieldMap)->Print();
    }
  else
    {
      FieldMap = new FrsSolenoidHypField();
      dynamic_cast<FrsSolenoidHypField*>(FieldMap)->SetPositionFromGeoManager("TransSetDet","FieldSolenoid");
      dynamic_cast<FrsSolenoidHypField*>(FieldMap)->SetField(0.,fac,SBz*0.1);
      dynamic_cast<FrsSolenoidHypField*>(FieldMap)->Print();
    }

  factor = fac;
  if(TMath::Abs(fac-1.)>1e-6)
    normalized = true;
  else
    normalized = false;


  if(Solenoid)
    {
      normalized = false;
      factor = 1.;
    }
}

void HypHIFrsMagneticField::GetFieldValue(const double Point[3],double *Bfield) const
{

  Double_t B[3];
  Double_t pos[3];
  
  //G4cout<<" MagField "<<Point[0]<<" "<<Point[1]<<" "<<Point[2]<<" ";

  pos[0]=Point[0]/cm;
  pos[1]=Point[1]/cm;
  pos[2]=Point[2]/cm;
  
  
  FieldMap->Field(pos,B);
  
  Bfield[0] = normalized ? B[0]*factor*kilogauss : B[0]*kilogauss;
  Bfield[1] = normalized ? B[1]*factor*kilogauss : B[1]*kilogauss;
  Bfield[2] = normalized ? B[2]*factor*kilogauss : B[2]*kilogauss;
  
  //G4cout<<"["<<pos[0]<<" "<<pos[1]<<" "<<pos[2]<<"] :"<<" "<<B[1]<<" / "<<Bfield[1]<<G4endl;

}
