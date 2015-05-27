#ifndef THypHi_ParCreator_header
#define THypHi_ParCreator_header 1

#include <iostream>
#include <fstream>
#include <string>

#include "globals.hh"
#include "THypHi_Par.hh"

/********************************************************************/
class THypHi_ParCreator
{
private:
  static void SetDafaultValues();
  static std::string GetNexWord(std::ifstream *infile);
  static G4double GetDimension(std::string dimension);
  static THypHi_Par* Par;
public:
  THypHi_ParCreator() {} 
  ~THypHi_ParCreator()
  {
    if(Par) 
      delete Par;
  }
  static void Init(std::string InputFileName);
  static THypHi_Par* GetParameter()
  {
    if(!Par)
      {
	std::cout << "!> Parameter should be initialysed first!!!\n";
	std::exit(1);
      }
    return Par;
  }
};

#endif
