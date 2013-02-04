#ifndef LYSOEventAction_h
#define LYSOEventAction_h 1

#include "G4UserEventAction.hh"

class LYSOEventAction : public G4UserEventAction
{
public:
	LYSOEventAction();
	~LYSOEventAction();

	void BeginOfEventAction(const G4Event*);
	void EndOfEventAction(const G4Event*);
	
};

#endif
