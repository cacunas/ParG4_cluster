#ifndef LYSOGeometry_h
#define LYSOGeomerty_h 1

#include "G4VUserDetectorConstruction.hh"
//#include "LYSORunAction.hh"
#include "LYSOSD.hh"
#include "G4VPhysicalVolume.hh"

class LYSOGeometry : public G4VUserDetectorConstruction
{

public:
	LYSOGeometry();	
	~LYSOGeometry();
	G4VPhysicalVolume* Construct();
	
private:
//	LYSORunAction* runAction;
	LYSOSD* pSD;
	G4VPhysicalVolume* pWorldPhys;
};

#endif
