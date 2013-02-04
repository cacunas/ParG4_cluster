#include "LYSOEventAction.hh"
#include "G4Event.hh"

LYSOEventAction::LYSOEventAction()
{}

LYSOEventAction::~LYSOEventAction()
{}

void LYSOEventAction::BeginOfEventAction(const G4Event* event){

	G4cout<<"Event "<<event->GetEventID()<<" start."<<G4endl;
}

void LYSOEventAction::EndOfEventAction(const G4Event* event){

	G4cout<<"Event "<<event->GetEventID()<<" done."<<G4endl;
}
