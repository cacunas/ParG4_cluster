
#include "globals.hh"
#include "LYSOPrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTypes.hh"

LYSOPrimaryGeneratorAction::LYSOPrimaryGeneratorAction()
	: G4VUserPrimaryGeneratorAction(),
	  particleGun(0)
{

	G4int n_particle = 1;
	particleGun = new G4ParticleGun(n_particle);
	particleGun->SetParticleDefinition(G4Gamma::Gamma());
	particleGun->SetParticleMomentumDirection(G4ThreeVector(0, -1, 0));
	particleGun->SetParticleEnergy(511*keV);
	particleGun->SetParticlePosition(G4ThreeVector(0, 10*mm, 0));

}

LYSOPrimaryGeneratorAction::~LYSOPrimaryGeneratorAction()
{

	delete particleGun;

}

void LYSOPrimaryGeneratorAction::GeneratePrimaries(G4Event* Event)
{
	
	particleGun->GeneratePrimaryVertex(Event);

}
