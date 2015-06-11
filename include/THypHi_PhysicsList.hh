#ifndef THypHi_PhysicsList_h
#define THypHi_PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
// #include "G4VUserPhysicsList.hh"
//#include "globals.hh"
#include "THypHi_Par.hh"

class THypHi_PhysicsList: public G4VModularPhysicsList{
    public:
	THypHi_PhysicsList(const THypHi_Par& _par);
	~THypHi_PhysicsList();
    
    protected:
	// Construct particle and physics
	void ConstructParticle();
	void ConstructProcess();
	void SetCuts();
   
    protected:
	// these methods Construct particles
	void ConstructBosons();
	void ConstructLeptons();
	void ConstructMesons();
	void ConstructBaryons();

    protected:
	// these methods Construct physics processes and register them
	void ConstructGeneral();
	void ConstructEM();

private :
  const THypHi_Par& Par;

};

#endif
