
#include "globals.hh"
#include "LYSOPhysicsList.hh"
#include "G4ParticleTypes.hh"
#include "G4ProcessManager.hh"
#include "G4PhysicsListHelper.hh"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4GammaConversionToMuons.hh"

#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"

#include "G4Scintillation.hh"


LYSOPhysicsList::LYSOPhysicsList()
{}

LYSOPhysicsList::~LYSOPhysicsList()
{}

void LYSOPhysicsList::ConstructParticle()
{

	G4Gamma::GammaDefinition();
	G4Electron::ElectronDefinition();
	G4Positron::PositronDefinition();
	G4OpticalPhoton::OpticalPhotonDefinition();

}

void LYSOPhysicsList::ConstructProcess()
{

	AddTransportation();
	ConstructEM();
	ConstructOp();
	ConstructScintillation();

}

void LYSOPhysicsList::ConstructEM()
{

	G4PhysicsListHelper* helper = G4PhysicsListHelper::GetPhysicsListHelper();
	G4ParticleDefinition* particle;

	//Gamma 
	particle = G4Gamma::Gamma();
	helper->RegisterProcess(new G4GammaConversion(), particle);     
	helper->RegisterProcess(new G4ComptonScattering(), particle);  
	helper->RegisterProcess(new G4PhotoElectricEffect(), particle);

	//Electron
	particle = G4Electron::Electron(); 
	helper->RegisterProcess(new G4eIonisation(), particle);
	helper->RegisterProcess(new G4eBremsstrahlung(), particle);  
	helper->RegisterProcess(new G4eMultipleScattering(), particle);    

	//Positron
	particle = G4Positron::Positron(); 
	helper->RegisterProcess(new G4eIonisation(), particle);
	helper->RegisterProcess(new G4eBremsstrahlung(), particle);
	helper->RegisterProcess(new G4eMultipleScattering(), particle);
	helper->RegisterProcess(new G4eplusAnnihilation(), particle);
     
}

void LYSOPhysicsList::ConstructOp()
{

	G4PhysicsListHelper* helper = G4PhysicsListHelper::GetPhysicsListHelper();
	G4ParticleDefinition* OpPhoton;

	OpPhoton = G4OpticalPhoton::OpticalPhoton();
	helper->RegisterProcess(new G4OpBoundaryProcess(), OpPhoton);
	helper->RegisterProcess(new G4OpAbsorption(), OpPhoton);
}

void LYSOPhysicsList::ConstructScintillation()
{

	G4Scintillation* Scint = new G4Scintillation("Scintillation");
	Scint->SetTrackSecondariesFirst(false);

	G4PhysicsListHelper* helper = G4PhysicsListHelper::GetPhysicsListHelper();
	theParticleIterator->reset();
	while( (*theParticleIterator)() ){
		G4ParticleDefinition* particle = theParticleIterator->value();
		if(Scint->IsApplicable(*particle)) helper->RegisterProcess(Scint, particle);
	}

}

void LYSOPhysicsList::SetCuts()
{

	SetCutsWithDefault();

}
