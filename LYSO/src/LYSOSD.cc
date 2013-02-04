
#include "LYSOSD.hh"
#include "LYSOHit.hh"
#include "LYSORunAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"
#include "G4OpticalPhoton.hh"
#include "G4SDManager.hh"
#include "G4StepPoint.hh"

LYSOSD::LYSOSD(const G4String& name, const G4String& hitsCName)
: G4VSensitiveDetector(name),
point(NULL),
hitsCollection(NULL),
energy(0),
pos(G4ThreeVector())
{
    collectionName.insert(hitsCName);
}

LYSOSD::~LYSOSD()
{
}

void LYSOSD::Initialize(G4HCofThisEvent* hce)
{

    hitsCollection =
            new LYSOHitsCollection(SensitiveDetectorName, collectionName[0]);
    G4int hcID =
            G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hce->AddHitsCollection(hcID, hitsCollection);
}

G4bool LYSOSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{

    point = step->GetPreStepPoint();
    pos = point->GetPosition();
    energy = point->GetKineticEnergy();

    LYSOHit* aHit = new LYSOHit(energy, pos);
    //aHit->Draw();
    hitsCollection->insert(aHit);

    return true;
}

void LYSOSD::EndOfEvent(G4HCofThisEvent*)
{

    //    G4int nHits = hitsCollection->entries();
    //    G4double tEnergy = 0;
    //
    //    G4EventManager* eManager = G4EventManager::GetEventManager();
    //    G4int event = eManager->GetNonconstCurrentEvent()->GetEventID();
    //
    //    for (G4int i = 0; i < nHits; i++) 
    //        tEnergy += (*hitsCollection)[i]->getEnergy();
    //    G4cout << "Event: " << event << "\tHits: " << nHits << "\tEnergy: " ;
    //    G4cout << tEnergy / eV << " eV" << G4endl;

    G4RunManager* runManager = G4RunManager::GetRunManager();
    G4int event = runManager->GetCurrentEvent()->GetEventID();
    LYSORunAction* runAction = (LYSORunAction*) runManager->GetUserRunAction();

    G4int nHits = hitsCollection->entries();
    G4double tEnergy = 0;

    for (G4int i = 0; i < nHits; i++) {
        energy = 1239.84193 / ((*hitsCollection)[i]->getEnergy() / eV); 
        //*** E = hc/wavelength [nm]***// 

        pos = (*hitsCollection)[i]->getPos();
        tEnergy += energy;
        G4cout << "Filling TNtuple" << G4endl; //DEBUG
        runAction->tuple->Fill(event, energy, pos(0), pos(1), pos(2));
    }
    if (nHits != 0) {
        G4cout << "Event: " << event << "\tHits: " << nHits;
        G4cout << "\tMean Energy: " << tEnergy / nHits << " [nm]" << G4endl;
    } else {
        G4cout << "Event: " << event << "\tHits: " << nHits;
        G4cout << "\tMean Energy: " << 0 << " [nm]" << G4endl;
    }
}

