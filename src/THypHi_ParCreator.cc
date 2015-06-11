#include "THypHi_ParCreator.hh"
#include "THypHi_Par.hh"

#include "G4SystemOfUnits.hh"

THypHi_Par* THypHi_ParCreator::Par = 0;

/********************************************************************/
#define READ_ONE_PARAM_DIMENSION_float(PARAM)\
    if(tstr == #PARAM){\
	G4double tmp;\
	tstr1 = GetNexWord(&infile);\
	if(tstr1 == "#") break;\
	tstr2 = GetNexWord(&infile);\
	if(tstr2 == "#") break;\
	tmp = std::atof(tstr1.c_str());\
	std::cout << "> Setting "<< #PARAM <<" to ";\
	std::cout << tmp << tstr2 << "\n";\
	tmp *= GetDimension(tstr2);\
	Par->Set_##PARAM (tmp);\
	ParamNotFound = false;\
    }
#define READ_ONE_PARAM_float(PARAM)\
    if(tstr == #PARAM){\
	G4double tmp;\
	tstr1 = GetNexWord(&infile);\
	if(tstr1 == "#") break;\
	tmp = std::atof(tstr1.c_str());\
	std::cout << "> Setting "<< #PARAM <<" to ";\
	std::cout << tmp << "\n";\
	Par->Set_##PARAM (tmp);\
	ParamNotFound = false;\
    }
#define READ_ONE_PARAM_int(PARAM)\
    if(tstr == #PARAM){\
	int tmp;\
	tstr1 = GetNexWord(&infile);\
	if(tstr1 == "#") break;\
	tmp = std::atoi(tstr1.c_str());\
	std::cout << "> Setting "<< #PARAM <<" to ";\
	std::cout << tmp << "\n";\
	Par->Set_##PARAM (tmp);\
	ParamNotFound = false;\
    }
#define READ_ONE_PARAM_string(PARAM)\
    if(tstr == #PARAM){\
	tstr1 = GetNexWord(&infile);\
	if(tstr1 == "#") break;\
	Par->Set_##PARAM (tstr1);\
	std::cout << "> Setting "<< #PARAM <<" to ";\
	std::cout << tstr1 << "\n";\
	ParamNotFound = false;\
    }
//-------------------------------------------------------------------
void THypHi_ParCreator::Init(std::string InputFileName){
    // Create the parametr object
    if(Par) delete Par;
    Par = new THypHi_Par();
    SetDafaultValues();
    // try to open input file
    std::ifstream infile(InputFileName.c_str());
    if(!infile){
	std::cerr << "!> Cannot open file";
	std::cerr << InputFileName << "\n";
	std::cerr << "!? Using default parameters!\n";
	return;
    }
    // Starting to read parameter file
    std::string tstr,tstr1,tstr2;
    while((!infile.eof())&&(!infile.fail())){
	bool ParamNotFound = true;
	tstr = GetNexWord(&infile);
	if(tstr == "#") break;
	//
	// PhysicsList subsection
	READ_ONE_PARAM_string(PhysicsListName);
	// Beam_* subsection
	READ_ONE_PARAM_string(Beam_Type);
	READ_ONE_PARAM_DIMENSION_float(Beam_KineticEnergy);
	READ_ONE_PARAM_DIMENSION_float(Beam_SpotSizeSigma);
	READ_ONE_PARAM_float(Beam_MomentumDirectionX);
	READ_ONE_PARAM_float(Beam_MomentumDirectionY);
	READ_ONE_PARAM_float(Beam_MomentumDirectionZ);
	READ_ONE_PARAM_int(RandomizePos)
	READ_ONE_PARAM_int(RandomizeEnergy)
	READ_ONE_PARAM_int(RandomizeDirection)
	//
	// CutValue_* subsection
	READ_ONE_PARAM_DIMENSION_float(CutValue_Default);
	READ_ONE_PARAM_DIMENSION_float(CutValue_Target);
	READ_ONE_PARAM_DIMENSION_float(CutValue_Plastic);
	//
	// HyperNuclei_* subsection
	// H4L
	READ_ONE_PARAM_DIMENSION_float(HyperNuclei_H4L_T12);
	READ_ONE_PARAM_float(HyperNuclei_H4L_br_mode1);
	READ_ONE_PARAM_float(HyperNuclei_H4L_br_mode2);
	READ_ONE_PARAM_float(HyperNuclei_H4L_br_mode3);
	READ_ONE_PARAM_float(HyperNuclei_H4L_br_mode4);
	// H3L
	READ_ONE_PARAM_DIMENSION_float(HyperNuclei_H3L_T12);
	READ_ONE_PARAM_float(HyperNuclei_H3L_br_mode1);
	READ_ONE_PARAM_float(HyperNuclei_H3L_br_mode2);
	READ_ONE_PARAM_float(HyperNuclei_H3L_br_mode3);
	READ_ONE_PARAM_float(HyperNuclei_H3L_br_mode4);
	READ_ONE_PARAM_float(HyperNuclei_H3L_br_mode5);
	// He4L
	READ_ONE_PARAM_DIMENSION_float(HyperNuclei_He4L_T12);
	READ_ONE_PARAM_float(HyperNuclei_He4L_br_mode1);
	READ_ONE_PARAM_float(HyperNuclei_He4L_br_mode2);
	READ_ONE_PARAM_float(HyperNuclei_He4L_br_mode3);
	READ_ONE_PARAM_float(HyperNuclei_He4L_br_mode4);
	READ_ONE_PARAM_float(HyperNuclei_He4L_br_mode5);
	// He5L
	READ_ONE_PARAM_DIMENSION_float(HyperNuclei_He5L_T12);
	READ_ONE_PARAM_float(HyperNuclei_He5L_br_mode1);
	READ_ONE_PARAM_float(HyperNuclei_He5L_br_mode2);
	//
	// Geometry_* subsection
	// World
	READ_ONE_PARAM_string(Geometry_WorldMaterial);
	READ_ONE_PARAM_DIMENSION_float(Geometry_WorldDimX);
	READ_ONE_PARAM_DIMENSION_float(Geometry_WorldDimY);
	READ_ONE_PARAM_DIMENSION_float(Geometry_WorldDimZ);
	// SKS field 
	READ_ONE_PARAM_float(Geometry_SKSField1);
	READ_ONE_PARAM_float(Geometry_SKSField2);
	// Target
	READ_ONE_PARAM_string(Geometry_TargetMaterial);
	READ_ONE_PARAM_DIMENSION_float(Geometry_TargetThickness);
	READ_ONE_PARAM_DIMENSION_float(Geometry_TargetHeight);
	READ_ONE_PARAM_DIMENSION_float(Geometry_TargetLength);
	READ_ONE_PARAM_DIMENSION_float(Geometry_TargetPosX);
	READ_ONE_PARAM_DIMENSION_float(Geometry_TargetPosY);
	READ_ONE_PARAM_DIMENSION_float(Geometry_TargetPosZ);
	// Fiber detectors
	READ_ONE_PARAM_int(Geometry_Fibers_Nlayers);
	READ_ONE_PARAM_DIMENSION_float(Geometry_Fibers_PlainsOfset);
	READ_ONE_PARAM_DIMENSION_float(Geometry_Fibers_ActiveRadius);
	READ_ONE_PARAM_DIMENSION_float(Geometry_Fibers_ExternalRadius);
	READ_ONE_PARAM_DIMENSION_float(Geometry_Fibers_ActiveLength);
	READ_ONE_PARAM_DIMENSION_float(Geometry_Fibers_z_TR1);
	READ_ONE_PARAM_DIMENSION_float(Geometry_Fibers_x_minus_TR1);
	READ_ONE_PARAM_DIMENSION_float(Geometry_Fibers_x_plus_TR1);
	READ_ONE_PARAM_DIMENSION_float(Geometry_Fibers_y_minus_TR1);
	READ_ONE_PARAM_DIMENSION_float(Geometry_Fibers_y_plus_TR1);
	READ_ONE_PARAM_DIMENSION_float(Geometry_Fibers_z_TR2);
	READ_ONE_PARAM_DIMENSION_float(Geometry_Fibers_x_minus_TR2);
	READ_ONE_PARAM_DIMENSION_float(Geometry_Fibers_x_plus_TR2);
	READ_ONE_PARAM_DIMENSION_float(Geometry_Fibers_y_minus_TR2);
	READ_ONE_PARAM_DIMENSION_float(Geometry_Fibers_y_plus_TR2);
	READ_ONE_PARAM_DIMENSION_float(Geometry_Fibers_tilt_angel_TR);
	// Alladin Magnet
	READ_ONE_PARAM_DIMENSION_float(Geometry_Alladin_Field);
	READ_ONE_PARAM_int(Aladin_FieldMap);
	// Alladin TOF wall
	READ_ONE_PARAM_DIMENSION_float(Geometry_AlladinTOF_PosX);
	READ_ONE_PARAM_DIMENSION_float(Geometry_AlladinTOF_PosY);
	READ_ONE_PARAM_DIMENSION_float(Geometry_AlladinTOF_PosZ);
	//TOF PLus
	READ_ONE_PARAM_DIMENSION_float(Geometry_TOFPlus_PosX);
	READ_ONE_PARAM_DIMENSION_float(Geometry_TOFPlus_PosY);
	READ_ONE_PARAM_DIMENSION_float(Geometry_TOFPlus_PosZ);
	// Universal Tracker
	if(tstr == "Detectors_UTracker"){
	    // material
	    tstr1 = GetNexWord(&infile);
	    if(tstr1 == "#") break;
	    Par->UTrackers_Material.push_back(tstr1);
	    // Dimensions and position
	    for(int k=0;k<9;k++){
		tstr1 = GetNexWord(&infile);
		if(tstr1 == "#") break;
		tstr2 = GetNexWord(&infile);
		if(tstr2 == "#") break;
		G4double tval =
		    std::atof(tstr1.c_str())*GetDimension(tstr2);
		switch(k){
		    case 0: Par->UTrackers_DimX.push_back(tval);
			    break;
		    case 1: Par->UTrackers_DimY.push_back(tval);
			    break;
		    case 2: Par->UTrackers_DimZ.push_back(tval);
			    break;
		    case 3: Par->UTrackers_PosX.push_back(tval);
			    break;
		    case 4: Par->UTrackers_PosY.push_back(tval);
			    break;
		    case 5: Par->UTrackers_PosZ.push_back(tval);
			    break;
		    case 6: Par->UTrackers_RotPhi.push_back(tval);
			    break;
		    case 7: Par->UTrackers_RotTheta.push_back(tval);
			    break;
		    case 8: Par->UTrackers_RotPsi.push_back(tval);
			    break;
		}
	    }
	    //
	    int ind = Par->UTrackers_Material.size()-1;
	    std::cout << "Add universal tracker made from ";
	    std::cout << Par->UTrackers_Material[ind] << "\n";
	    std::cout << " dimensions: ";
	    std::cout << Par->UTrackers_DimX[ind] << "; ";
	    std::cout << Par->UTrackers_DimY[ind] << "; ";
	    std::cout << Par->UTrackers_DimZ[ind] << ";\n at: ";
	    std::cout << Par->UTrackers_PosX[ind] << "; ";
	    std::cout << Par->UTrackers_PosY[ind] << "; ";
	    std::cout << Par->UTrackers_PosZ[ind] << ";\n";
	    std::cout << " rotades as: ";
	    std::cout << Par->UTrackers_RotPhi[ind] << "; ";
	    std::cout << Par->UTrackers_RotTheta[ind] << "; ";
	    std::cout << Par->UTrackers_RotPsi[ind] << ";\n";
	    ParamNotFound = false;
	}
	// Universal Absorber
	if(tstr == "Detectors_UAbsorber"){
	    // material
	    tstr1 = GetNexWord(&infile);
	    if(tstr1 == "#") break;
	    Par->UAbsorbers_Material.push_back(tstr1);
	    // Dimensions and position
	    for(int k=0;k<9;k++){
		tstr1 = GetNexWord(&infile);
		if(tstr1 == "#") break;
		tstr2 = GetNexWord(&infile);
		if(tstr2 == "#") break;
		G4double tval =
		    std::atof(tstr1.c_str())*GetDimension(tstr2);
		switch(k){
		    case 0: Par->UAbsorbers_DimX.push_back(tval);
			    break;
		    case 1: Par->UAbsorbers_DimY.push_back(tval);
			    break;
		    case 2: Par->UAbsorbers_DimZ.push_back(tval);
			    break;
		    case 3: Par->UAbsorbers_PosX.push_back(tval);
			    break;
		    case 4: Par->UAbsorbers_PosY.push_back(tval);
			    break;
		    case 5: Par->UAbsorbers_PosZ.push_back(tval);
			    break;
		    case 6: Par->UAbsorbers_RotPhi.push_back(tval);
			    break;
		    case 7: Par->UAbsorbers_RotTheta.push_back(tval);
			    break;
		    case 8: Par->UAbsorbers_RotPsi.push_back(tval);
			    break;
		}
	    }
	    //
	    int ind = Par->UAbsorbers_Material.size()-1;
	    std::cout << "Add universal absorber made from ";
	    std::cout << Par->UAbsorbers_Material[ind] << "\n";
	    std::cout << " dimensions: ";
	    std::cout << Par->UAbsorbers_DimX[ind] << "; ";
	    std::cout << Par->UAbsorbers_DimY[ind] << "; ";
	    std::cout << Par->UAbsorbers_DimZ[ind] << ";\n at: ";
	    std::cout << Par->UAbsorbers_PosX[ind] << "; ";
	    std::cout << Par->UAbsorbers_PosY[ind] << "; ";
	    std::cout << Par->UAbsorbers_PosZ[ind] << ";\n";
	    std::cout << " rotades as: ";
	    std::cout << Par->UAbsorbers_RotPhi[ind] << "; ";
	    std::cout << Par->UAbsorbers_RotTheta[ind] << "; ";
	    std::cout << Par->UAbsorbers_RotPsi[ind] << ";\n";
	    ParamNotFound = false;
	}
	//
	if(ParamNotFound){
	    std::cout << "?> Parameter " << tstr;
	    std::cout << " NOT FOUND!!!\n";
	}
    }

    // Closing input file
    infile.close();
}
//-------------------------------------------------------------------
#undef READ_ONE_PARAM_DIMENSION_float
#undef READ_ONE_PARAM_float
#undef READ_ONE_PARAM_string
#undef READ_ONE_PARAM_int

/********************************************************************/
#define SET_PARAMETER(PARAM,VALUE)\
    Par->Set_##PARAM (VALUE)
//-------------------------------------------------------------------
void THypHi_ParCreator::SetDafaultValues(){
    /**** Set default values for parameters ****/

    SET_PARAMETER(PhysicsListName,"G4Default_FTFP_BERT");
    /*--- Beam_* subsection ---*/
    SET_PARAMETER(Beam_Type,"H4L");
    SET_PARAMETER(Beam_KineticEnergy,4.0*GeV);
    SET_PARAMETER(Beam_SpotSizeSigma,1.0*cm);
    SET_PARAMETER(Beam_MomentumDirectionX,0.0);
    SET_PARAMETER(Beam_MomentumDirectionY,0.0);
    SET_PARAMETER(Beam_MomentumDirectionZ,1.0);
    SET_PARAMETER(RandomizePos,0);
    SET_PARAMETER(RandomizeEnergy,0);
    SET_PARAMETER(RandomizeDirection,0);
    /*--- CutValue_* subsection ---*/
    SET_PARAMETER(CutValue_Default,1.0*mm);
    SET_PARAMETER(CutValue_Target,0.1*mm);
    SET_PARAMETER(CutValue_Plastic,0.01*mm);
    /*--- HyperNuclei_* subsection ---*/
    // H4L
    SET_PARAMETER(HyperNuclei_H4L_T12,0.194*ns);
    SET_PARAMETER(HyperNuclei_H4L_br_mode1,0.25);
    SET_PARAMETER(HyperNuclei_H4L_br_mode2,0.25);
    SET_PARAMETER(HyperNuclei_H4L_br_mode3,0.25);
    SET_PARAMETER(HyperNuclei_H4L_br_mode4,0.25);
    // H3L
    SET_PARAMETER(HyperNuclei_H3L_T12,0.246*ns);
    SET_PARAMETER(HyperNuclei_H3L_br_mode1,0.2);
    SET_PARAMETER(HyperNuclei_H3L_br_mode2,0.2);
    SET_PARAMETER(HyperNuclei_H3L_br_mode3,0.2);
    SET_PARAMETER(HyperNuclei_H3L_br_mode4,0.2);
    SET_PARAMETER(HyperNuclei_H3L_br_mode4,0.2);
    // He4L
    SET_PARAMETER(HyperNuclei_He4L_T12,0.256*ns);
    SET_PARAMETER(HyperNuclei_He4L_br_mode1,0.2);
    SET_PARAMETER(HyperNuclei_He4L_br_mode2,0.2);
    SET_PARAMETER(HyperNuclei_He4L_br_mode3,0.2);
    SET_PARAMETER(HyperNuclei_He4L_br_mode4,0.2);
    SET_PARAMETER(HyperNuclei_He4L_br_mode5,0.2);
    // He5L
    SET_PARAMETER(HyperNuclei_He5L_T12,0.256*ns);
    SET_PARAMETER(HyperNuclei_He5L_br_mode1,0.25);
    SET_PARAMETER(HyperNuclei_He5L_br_mode2,0.25);
    /*--- Geometry_* subsection ---*/
    // World
    SET_PARAMETER(Geometry_WorldMaterial,"Air");
    SET_PARAMETER(Geometry_WorldDimX,5*m);
    SET_PARAMETER(Geometry_WorldDimY,5*m);
    SET_PARAMETER(Geometry_WorldDimZ,10*m);
    // Target
    SET_PARAMETER(Geometry_TargetMaterial,"C");
    SET_PARAMETER(Geometry_TargetThickness,4.44*cm);
    SET_PARAMETER(Geometry_TargetHeight,5.0*cm);
    SET_PARAMETER(Geometry_TargetLength,5.0*cm);
    SET_PARAMETER(Geometry_TargetPosX,0.0*mm);
    SET_PARAMETER(Geometry_TargetPosY,0.0*mm);
    SET_PARAMETER(Geometry_TargetPosZ,0.0*mm);
    // Fiber detectors
    SET_PARAMETER(Geometry_Fibers_Nlayers,2);
    SET_PARAMETER(Geometry_Fibers_PlainsOfset,0.5*cm);
    SET_PARAMETER(Geometry_Fibers_ActiveRadius,0.415*mm-0.05*mm);
    SET_PARAMETER(Geometry_Fibers_ExternalRadius,0.415*mm);
    SET_PARAMETER(Geometry_Fibers_ActiveLength,15*cm);
    SET_PARAMETER(Geometry_Fibers_z_TR1,40.0*cm);
    SET_PARAMETER(Geometry_Fibers_x_minus_TR1,-2.0*cm);
    SET_PARAMETER(Geometry_Fibers_x_plus_TR1,8.0*cm);
    SET_PARAMETER(Geometry_Fibers_y_minus_TR1,-2.0*cm);
    SET_PARAMETER(Geometry_Fibers_y_plus_TR1,2.0*cm);
    SET_PARAMETER(Geometry_Fibers_z_TR2,70.0*cm);
    SET_PARAMETER(Geometry_Fibers_x_minus_TR2,-3.0*cm);
    SET_PARAMETER(Geometry_Fibers_x_plus_TR2,15.0*cm);
    SET_PARAMETER(Geometry_Fibers_y_minus_TR2,-4.0*cm);
    SET_PARAMETER(Geometry_Fibers_y_plus_TR2,4.0*cm);
    SET_PARAMETER(Geometry_Fibers_tilt_angel_TR,45*deg);
    // Alladin Magnet
    SET_PARAMETER(Geometry_Alladin_Field,-0.7*tesla);
    SET_PARAMETER(Aladin_FieldMap,0);
    // Alladin TOF wall
    SET_PARAMETER(Geometry_AlladinTOF_PosX,-1.55*m);
    SET_PARAMETER(Geometry_AlladinTOF_PosY,0.0*m);
    SET_PARAMETER(Geometry_AlladinTOF_PosZ,7.35*m);
    // TOF Plus wall
    SET_PARAMETER(Geometry_AlladinTOF_PosX,0.475*m);
    SET_PARAMETER(Geometry_AlladinTOF_PosY,0.0*m);
    SET_PARAMETER(Geometry_AlladinTOF_PosZ,7.35*m);
    
}
#undef SET_PARAMETER

/********************************************************************/
G4double THypHi_ParCreator::GetDimension(std::string dimension){
    // Time
    if(dimension == "ns") return ns;
    if(dimension == "ms") return ms;
    if(dimension == "s") return s;
    // Length
    if(dimension == "m") return m;
    if(dimension == "cm") return cm;
    if(dimension == "mm") return mm;
    // Fields
    if(dimension == "tesla") return tesla;
    if(dimension == "kG") return kilogauss;
    // Energy
    if(dimension == "eV") return eV;
    if(dimension == "keV") return keV;
    if(dimension == "MeV") return MeV;
    if(dimension == "GeV") return GeV;
    // Angle
    if(dimension == "degree") return deg;
    if(dimension == "rad") return rad;
    //
    std::cerr << "!> Unckown dimension " << dimension << "\n";
    std::cerr << "!> Exiting !!!\n";
    std::exit(1);
    return 0;
}

/********************************************************************/
std::string THypHi_ParCreator::GetNexWord(std::ifstream *infile){
    // scipp commented lines #...
    std::string result = "#";
    while(result[0] == '#'){
	(*infile) >> result;
	if(infile->eof() || infile->fail()) return "#";
	if(result[0] == '#'){
	    char comm = infile->get();
	    while((comm != '\n')&&(!infile->eof())&&(!infile->fail()))
		comm = infile->get();
	}
    }
    if(infile->eof() || infile->fail()) result = "#";
    return result;
}
