
#include "globals.hh"
#include "LYSORunAction.hh"
#include "G4Run.hh"
#include "TFile.h"
#include "TNtupleD.h"

LYSORunAction::LYSORunAction()
: G4UserRunAction(),
tuple(0),
file(0)
{
}

LYSORunAction::~LYSORunAction()
{
}

void LYSORunAction::BeginOfRunAction(const G4Run* run)
{
    G4cout << "Run " << run->GetRunID() << " start." << G4endl;

        file = new TFile("LYSO.root", "UPDATE");
        tuple = new TNtupleD("Tuple","Data Tuple","event:energy:pos_x:pos_y:pos_z");

}

void LYSORunAction::EndOfRunAction(const G4Run* run)
{

    G4cout << "Run " << run->GetRunID() << " done." << G4endl;
        tuple->Write("Tuple");
        delete tuple;
        file->Close();

}
