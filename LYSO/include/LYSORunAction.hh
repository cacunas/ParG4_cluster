#ifndef LYSORunAction_h
#define LYSORunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"
#include "TNtupleD.h"
#include "TFile.h"


class G4Run;

class LYSORunAction : public G4UserRunAction {
public:
    LYSORunAction();
    ~LYSORunAction();

    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
    TNtupleD* tuple;

private:
    TFile* file;
};

#endif

