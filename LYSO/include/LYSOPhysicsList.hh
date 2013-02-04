#ifndef LYSOPhysicsList_h 
#define LYSOPhysicsList_h 1

#include "G4VUserPhysicsList.hh"

class LYSOPhysicsList: public G4VUserPhysicsList
{

public:

	LYSOPhysicsList();
	~LYSOPhysicsList();

private:

	void ConstructParticle();
	void ConstructProcess();
	void SetCuts();

	void ConstructEM();
	void ConstructOp();
	void ConstructScintillation();

};

#endif
