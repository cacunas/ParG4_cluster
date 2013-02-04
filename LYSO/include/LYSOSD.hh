#ifndef LYSOSD_h
#define LYSOSD_h 1

#include "G4VSensitiveDetector.hh"
#include "LYSOHit.hh"
#include "G4StepPoint.hh"
#include "G4ThreeVector.hh"
#include "G4HCofThisEvent.hh"

class LYSOSD : public G4VSensitiveDetector
{

public:
	LYSOSD(const G4String&, const G4String&);
	~LYSOSD();
  
	void	Initialize(G4HCofThisEvent*);
	G4bool	ProcessHits(G4Step*, G4TouchableHistory*);
	void	EndOfEvent(G4HCofThisEvent*);

private:
	G4StepPoint* point;
	LYSOHitsCollection* hitsCollection;	
	G4double energy;
	G4ThreeVector pos;
};

#endif
