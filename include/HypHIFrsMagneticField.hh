#ifndef HypHIFrs_MagneticField_H
#define HypHIFrs_MagneticField_H

#include "globals.hh"
#include "G4MagneticField.hh"
#include "FairField.h"

#include "FrsSksHypFieldMapFull.h"
#include "FrsSolenoidHypField.h"

class G4FieldManager;


class HypHIFrsMagneticField : public G4MagneticField
{
    public:
  HypHIFrsMagneticField(const G4String& namefile_field);
  ~HypHIFrsMagneticField();
  //                                                                                                                                                              
  void GetFieldValue( const  double Point[3], double *Bfield ) const;
  void InitField(double fac =1.,bool SecondM = false,double Sbz = 10.,bool Solenoid=false);
private:

  FairField* FieldMap;

  G4String namefield;

  //double telsa;
  double factor;
  bool normalized;
  


};

#endif

