#ifndef LYSOPrimaryGeneratorAction_h
#define LYSOPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"


class LYSOPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{

public:

	LYSOPrimaryGeneratorAction();
	~LYSOPrimaryGeneratorAction();
	void GeneratePrimaries(G4Event*);

private:

	G4ParticleGun* particleGun;

};

#endif
