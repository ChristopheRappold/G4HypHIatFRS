#ifndef THypHi_Par_header
#define THypHi_Par_header 1

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "TNamed.h"

/********************************************************************/
#define THypHi_DEF_PAR(TYPE,PARAMETR)\
    private: TYPE PARAMETR;\
    public: TYPE Get_##PARAMETR () const {return PARAMETR;};\
            void Set_##PARAMETR (TYPE val){PARAMETR = val;}

/********************************************************************/
class THypHi_Par:public TNamed{
    /****************************/
    /**** Parameters section ****/
    /*--- Beam_* subsection ---*/
    THypHi_DEF_PAR(std::string,PhysicsListName);
    /*--- Beam_* subsection ---*/
    THypHi_DEF_PAR(std::string,Beam_Type);
    THypHi_DEF_PAR(Double_t,Beam_KineticEnergy);
    THypHi_DEF_PAR(Double_t,Beam_SpotSizeSigma);
    THypHi_DEF_PAR(Double_t,Beam_MomentumDirectionX);
    THypHi_DEF_PAR(Double_t,Beam_MomentumDirectionY);
    THypHi_DEF_PAR(Double_t,Beam_MomentumDirectionZ);
    THypHi_DEF_PAR(Int_t,RandomizePos);
    THypHi_DEF_PAR(Int_t,RandomizeEnergy);
    THypHi_DEF_PAR(Int_t,RandomizeDirection);
    /*--- CutValue_* subsection ---*/
    THypHi_DEF_PAR(Double_t,CutValue_Default);
    THypHi_DEF_PAR(Double_t,CutValue_Target);
    THypHi_DEF_PAR(Double_t,CutValue_Plastic);
    /*--- HyperNuclei_* subsection ---*/
    // H4L
    THypHi_DEF_PAR(Double_t,HyperNuclei_H4L_T12);
    THypHi_DEF_PAR(Double_t,HyperNuclei_H4L_br_mode1);
    THypHi_DEF_PAR(Double_t,HyperNuclei_H4L_br_mode2);
    THypHi_DEF_PAR(Double_t,HyperNuclei_H4L_br_mode3);
    THypHi_DEF_PAR(Double_t,HyperNuclei_H4L_br_mode4);
    // H3L
    THypHi_DEF_PAR(Double_t,HyperNuclei_H3L_T12);
    THypHi_DEF_PAR(Double_t,HyperNuclei_H3L_br_mode1);
    THypHi_DEF_PAR(Double_t,HyperNuclei_H3L_br_mode2);
    THypHi_DEF_PAR(Double_t,HyperNuclei_H3L_br_mode3);
    THypHi_DEF_PAR(Double_t,HyperNuclei_H3L_br_mode4);
    THypHi_DEF_PAR(Double_t,HyperNuclei_H3L_br_mode5);
    // He4L
    THypHi_DEF_PAR(Double_t,HyperNuclei_He4L_T12);
    THypHi_DEF_PAR(Double_t,HyperNuclei_He4L_br_mode1);
    THypHi_DEF_PAR(Double_t,HyperNuclei_He4L_br_mode2);
    THypHi_DEF_PAR(Double_t,HyperNuclei_He4L_br_mode3);
    THypHi_DEF_PAR(Double_t,HyperNuclei_He4L_br_mode4);
    THypHi_DEF_PAR(Double_t,HyperNuclei_He4L_br_mode5);
    // He4L
    THypHi_DEF_PAR(Double_t,HyperNuclei_He5L_T12);
    THypHi_DEF_PAR(Double_t,HyperNuclei_He5L_br_mode1);
    THypHi_DEF_PAR(Double_t,HyperNuclei_He5L_br_mode2);
    /*--- Geometry_* subsection ---*/
    // World
    THypHi_DEF_PAR(std::string,Geometry_WorldMaterial);
    THypHi_DEF_PAR(Double_t,Geometry_WorldDimX);
    THypHi_DEF_PAR(Double_t,Geometry_WorldDimY);
    THypHi_DEF_PAR(Double_t,Geometry_WorldDimZ);
    // SKS field  
    THypHi_DEF_PAR(Double_t,Geometry_SKSField1);
    THypHi_DEF_PAR(Double_t,Geometry_SKSField2);

    // Target
    THypHi_DEF_PAR(std::string,Geometry_TargetMaterial);
    THypHi_DEF_PAR(Double_t,Geometry_TargetThickness);
    THypHi_DEF_PAR(Double_t,Geometry_TargetHeight);
    THypHi_DEF_PAR(Double_t,Geometry_TargetLength);
    THypHi_DEF_PAR(Double_t,Geometry_TargetPosX);
    THypHi_DEF_PAR(Double_t,Geometry_TargetPosY);
    THypHi_DEF_PAR(Double_t,Geometry_TargetPosZ);
    // Fiber detectors
    THypHi_DEF_PAR(Int_t,Geometry_Fibers_Nlayers);
    THypHi_DEF_PAR(Double_t,Geometry_Fibers_PlainsOfset);
    THypHi_DEF_PAR(Double_t,Geometry_Fibers_ActiveRadius);
    THypHi_DEF_PAR(Double_t,Geometry_Fibers_ExternalRadius);
    THypHi_DEF_PAR(Double_t,Geometry_Fibers_ActiveLength);
    THypHi_DEF_PAR(Double_t,Geometry_Fibers_z_TR1);
    THypHi_DEF_PAR(Double_t,Geometry_Fibers_x_minus_TR1);
    THypHi_DEF_PAR(Double_t,Geometry_Fibers_x_plus_TR1);
    THypHi_DEF_PAR(Double_t,Geometry_Fibers_y_minus_TR1);
    THypHi_DEF_PAR(Double_t,Geometry_Fibers_y_plus_TR1);
    THypHi_DEF_PAR(Double_t,Geometry_Fibers_z_TR2);
    THypHi_DEF_PAR(Double_t,Geometry_Fibers_x_minus_TR2);
    THypHi_DEF_PAR(Double_t,Geometry_Fibers_x_plus_TR2);
    THypHi_DEF_PAR(Double_t,Geometry_Fibers_y_minus_TR2);
    THypHi_DEF_PAR(Double_t,Geometry_Fibers_y_plus_TR2);
    THypHi_DEF_PAR(Double_t,Geometry_Fibers_tilt_angel_TR);
    // Alladin Magnet
    THypHi_DEF_PAR(Double_t,Geometry_Alladin_Field);
    THypHi_DEF_PAR(Int_t,Aladin_FieldMap);
    // Alladin TOF
    THypHi_DEF_PAR(Double_t,Geometry_AlladinTOF_PosX);
    THypHi_DEF_PAR(Double_t,Geometry_AlladinTOF_PosY);
    THypHi_DEF_PAR(Double_t,Geometry_AlladinTOF_PosZ);
    // TOF Plus
    THypHi_DEF_PAR(Double_t,Geometry_TOFPlus_PosX);
    THypHi_DEF_PAR(Double_t,Geometry_TOFPlus_PosY);
    THypHi_DEF_PAR(Double_t,Geometry_TOFPlus_PosZ);
    
    /*------------------------------------------------------------*/
    // Universal Trackers
    public:
	std::vector<std::string> UTrackers_Material;
	std::vector<Double_t> UTrackers_PosX;
	std::vector<Double_t> UTrackers_PosY;
	std::vector<Double_t> UTrackers_PosZ;
	std::vector<Double_t> UTrackers_DimX;
	std::vector<Double_t> UTrackers_DimY;
	std::vector<Double_t> UTrackers_DimZ;
	std::vector<Double_t> UTrackers_RotPhi;
	std::vector<Double_t> UTrackers_RotTheta;
	std::vector<Double_t> UTrackers_RotPsi;
    /*------------------------------------------------------------*/
    // Universal Absorbers
    public:
	std::vector<std::string> UAbsorbers_Material;
	std::vector<Double_t> UAbsorbers_PosX;
	std::vector<Double_t> UAbsorbers_PosY;
	std::vector<Double_t> UAbsorbers_PosZ;
	std::vector<Double_t> UAbsorbers_DimX;
	std::vector<Double_t> UAbsorbers_DimY;
	std::vector<Double_t> UAbsorbers_DimZ;
	std::vector<Double_t> UAbsorbers_RotPhi;
	std::vector<Double_t> UAbsorbers_RotTheta;
	std::vector<Double_t> UAbsorbers_RotPsi;
    /*------------------------------------------------------------*/
    public:
	THypHi_Par(){SetName("HypHiMc_Par");};
	~THypHi_Par(){};
    /*------------------------------------------------------------*/
    ClassDef(THypHi_Par,1); // THypHi_Par
};

#undef THypHi_DEF_PAR

ClassImp(THypHi_Par)

#endif
