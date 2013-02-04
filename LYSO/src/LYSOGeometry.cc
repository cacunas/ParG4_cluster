
#include "globals.hh"

#include "LYSOGeometry.hh"
#include "LYSOSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Element.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4SDManager.hh"
#include "G4MaterialPropertyVector.hh"
#include "G4VSDFilter.hh"
#include "G4SDParticleFilter.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"

LYSOGeometry::LYSOGeometry()
	: pSD(0),
	  pWorldPhys(0)
{}

LYSOGeometry::~LYSOGeometry()
{}

G4VPhysicalVolume* LYSOGeometry::Construct()
{

//LYSO Material____________________________________________________________

//Get Elements From Material Data Base
G4NistManager* manager = G4NistManager::Instance();

G4Element* Oxigen   = manager->FindOrBuildElement("O");
G4Element* Lutetium = manager->FindOrBuildElement("Lu");
G4Element* Yttrium  = manager->FindOrBuildElement("Y");

//Air
G4Material* Air  = manager->FindOrBuildMaterial("G4_AIR");

//Lutetium Oxide Lu2O3
G4Material* LutetiumOxide = new G4Material("LutetiumOxide", 9.41*g/cm3, 2);
LutetiumOxide->AddElement(Lutetium, 2);	
LutetiumOxide->AddElement(Oxigen, 3);

//Silicon Dioxide SiO2
G4Material* SiliconDioxide  = manager->FindOrBuildMaterial("G4_SILICON_DIOXIDE");

//Yttrium Oxide Y2O3
G4Material* YttriumOxide = new G4Material("YttriumOxide", 5.01*g/cm3, 2);
YttriumOxide->AddElement(Yttrium, 2);
YttriumOxide->AddElement(Oxigen, 3);

//Build LYSO Material
G4Material* LYSO = new G4Material("LYSO", 7.1*g/cm3, 3);
LYSO->AddMaterial(LutetiumOxide,  81*perCent);
LYSO->AddMaterial(SiliconDioxide, 14*perCent);
LYSO->AddMaterial(YttriumOxide,    5*perCent);				


//Optical properties Attached to Crystal_____________________________

const G4int num = 21;
G4double ene[num]   =  {1.79*eV, 1.85*eV, 1.91*eV, 1.97*eV,
			2.04*eV, 2.11*eV, 2.19*eV, 2.27*eV,
			2.36*eV, 2.45*eV, 2.56*eV, 2.67*eV,
			2.80*eV, 2.94*eV, 3.09*eV, 3.25*eV,
			3.44*eV, 3.65*eV, 3.89*eV, 4.16*eV,
			4.43*eV};

G4double fast[num]  =  {0.01, 0.10, 0.20, 0.50,
			0.90, 1.70, 2.90, 5.00,
			8.30, 12.5, 17.0, 22.9,
			26.4, 25.6, 16.8, 4.20,
			0.30, 0.20, 0.10, 0.01,
			0.00};

G4double rLyso[num] =  {1.81, 1.81, 1.81, 1.81,
			1.81, 1.81, 1.81, 1.81,
			1.81, 1.81, 1.81, 1.81,
			1.81, 1.81, 1.81, 1.81,
			1.81, 1.81, 1.81, 1.81,
			1.81};
G4double rAir[num]  =  {1.00, 1.00, 1.00, 1.00,
			1.00, 1.00, 1.00, 1.00,
			1.00, 1.00, 1.00, 1.00,
			1.00, 1.00, 1.00, 1.00,
			1.00, 1.00, 1.00, 1.00,
			1.00};

G4double abs[num]   =  {50*cm, 50*cm, 50*cm, 50*cm,
			50*cm, 50*cm, 50*cm, 50*cm,
			50*cm, 50*cm, 50*cm, 50*cm,
			50*cm, 50*cm, 50*cm, 50*cm,
			50*cm, 50*cm, 50*cm, 50*cm,
			50*cm};

G4MaterialPropertiesTable* mpt1 = new G4MaterialPropertiesTable();
G4MaterialPropertiesTable* mpt2 = new G4MaterialPropertiesTable();

mpt1->AddProperty("FASTCOMPONENT", ene, fast, num);
mpt1->AddProperty("RINDEX", ene, rLyso , num);
mpt1->AddProperty("ABSLENGTH", ene, abs, num);
mpt1->AddConstProperty("SCINTILLATIONYIELD",32./keV);
mpt1->AddConstProperty("RESOLUTIONSCALE", 1);
mpt1->AddConstProperty("FASTTIMECONSTANT",41*ns);

mpt2->AddProperty("RINDEX" , ene, rAir , num);

LYSO->SetMaterialPropertiesTable(mpt1);
Air->SetMaterialPropertiesTable(mpt2);


//Volumes Definition________________________________________

//Parameters--------

G4ThreeVector Id_tr(0,0,0);
G4RotationMatrix* Id_rot = new G4RotationMatrix(0,0,0);

//Sensitive Detector
G4double SDz = 0.725*mm;
G4double Gap = 0.01*mm; 

//Crystal
G4double Cx = 2*mm;
G4double Cy = 2*mm;
G4double Cz = 22.5*mm;

//Gap
G4double Gx = Cx+0.01*mm;
G4double Gy = Cy+0.01*mm;
G4double Gz = Cz;

//World
G4double Wx = Gx+10*mm;
G4double Wy = Gy+10*mm;
G4double Wz = Gz+10*mm;

//Construction-------------

//World
G4Box* pWorldSolid = new G4Box("WorldBox", Wx, Wy, Wz);
G4LogicalVolume* pWorldLog = new G4LogicalVolume(pWorldSolid, Air, "WorldLogical");
pWorldPhys = new G4PVPlacement(Id_rot, Id_tr, pWorldLog, "World", 0, false, 0);
//pWorldLog->SetVisAttributes(G4VisAttributes::GetInvisible());

//Gap
G4Box* pGapSolid = new G4Box("GapBox", Gx, Gy, Gz);
G4LogicalVolume* pGapLog = new G4LogicalVolume(pGapSolid, Air, "GapLogical");
G4PVPlacement* pGapPhys = new G4PVPlacement(Id_rot, Id_tr, pGapLog, "Gap", pWorldLog, false, 0);
pGapLog->SetVisAttributes(G4VisAttributes::GetInvisible());

//Crystal
G4Box* pCrySolid = new G4Box("CrystalBox", Cx, Cy, Cz);
G4LogicalVolume* pCryLog = new G4LogicalVolume(pCrySolid, LYSO, "CrystalLogical");
G4PVPlacement* pCrystalPhys = new G4PVPlacement(Id_rot, Id_tr, pCryLog, "Crystal", pGapLog, false, 0);

//Sensitive Detector
G4Box* pSDSolid = new G4Box("SDBox", Cx, Cy, SDz);
G4LogicalVolume* pSDLog = new G4LogicalVolume(pSDSolid, Air,"SDLogical");
pSDLog->SetVisAttributes(G4VisAttributes::GetInvisible());

//Sensitive Detectors_______________________________________________________

pSD = new LYSOSD("LYSO/SensitiveDetector","LYSOHitsCollection");
G4SDParticleFilter* particleFilter = new G4SDParticleFilter("PhotonFilter","opticalphoton");
pSD->SetFilter(particleFilter);

G4SDManager* sdm = G4SDManager::GetSDMpointer();
sdm->AddNewDetector(pSD);

pSDLog->SetSensitiveDetector(pSD);
new G4PVPlacement(Id_rot,G4ThreeVector(0, 0, Cz+SDz+Gap), pSDLog, "SDFront", pWorldLog, false, 0);
new G4PVPlacement(Id_rot,G4ThreeVector(0, 0,-Cz-SDz-Gap), pSDLog, "SDRear",  pWorldLog, false, 0);

//Material Properties Tables Attached to Optical Surface___________________

const G4int n = 2;

G4double pp[n] = {1.70*eV, 4.50*eV};
G4double reflectivity[n] = {0.97, 0.97};
G4double efficiency[n] = {0.0, 0.0};

G4double rindex[n] = {1.575, 1.575};		//Refractive index of Aluminized Mylar (Mylar in this case, data from wikipedia)
G4double specularlobe[n] = {0.1, 0.1};		//Probability of specular-reflection about the normal of a micro-facet
G4double specularspike[n] = {0.8, 0.8};	 	//Probability of specular reflection about the average normal
G4double backscatter[n] = {0.0, 0.0};		//Probability of backward reflection (For Normal Incidence)
						//**Probability of Lambertian reflection is 1 minus the previus probabilities**

G4MaterialPropertiesTable* SMPT = new G4MaterialPropertiesTable();

SMPT->AddProperty("RINDEX",pp,rindex,n);
SMPT->AddProperty("SPECULARLOBECONSTANT",pp,specularlobe,n);
SMPT->AddProperty("SPECULARSPIKECONSTANT",pp,specularspike,n);
SMPT->AddProperty("BACKSCATTERCONSTANT",pp,backscatter,n);
SMPT->AddProperty("REFLECTIVITY",pp,reflectivity,n);
SMPT->AddProperty("EFFICIENCY",pp,efficiency,n);

//Optical Surface___________________________________________________________

G4OpticalSurface* opSurface = new G4OpticalSurface("OpticalSurface");
opSurface->SetModel(unified);
opSurface->SetType(dielectric_dielectric);
opSurface->SetFinish(polishedbackpainted);
//polishedfrontpainted just use reflectivity, all of the other paramenters just in case we change this model.

G4double sigma_alpha = 0.1;
opSurface->SetSigmaAlpha(sigma_alpha);
opSurface->SetMaterialPropertiesTable(SMPT);

new G4LogicalBorderSurface("CrystalSurface",pCrystalPhys,pGapPhys,opSurface);


return pWorldPhys;
}
