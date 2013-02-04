
#include "globals.hh"
#include "LYSOGeometry.hh"
#include "LYSOPhysicsList.hh"
#include "LYSOPrimaryGeneratorAction.hh"
#include "LYSORunAction.hh"
//#include "LYSOEventAction.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"
#include <time.h>

// For threading **************************************************************
#include "ParTopC.icc"

int main(int argc,char** argv){

	G4Random::setTheEngine(new CLHEP::RanecuEngine);
	G4long seed = time(0);
	G4Random::setTheSeed(seed);

	G4RunManager* runManager = new G4RunManager;

	//User actions
	LYSOPhysicsList* thePhysics = new LYSOPhysicsList();
	runManager->SetUserInitialization(thePhysics);
		
	LYSOPrimaryGeneratorAction* theGenerator = new LYSOPrimaryGeneratorAction();
	runManager->SetUserAction(theGenerator);

	LYSORunAction* runAction = new LYSORunAction();
	runManager->SetUserAction(runAction);

//	LYSOEventAction* evAction = new LYSOEventAction();
//	runManager->SetUserAction(evAction);

	LYSOGeometry* theGeometry = new LYSOGeometry();
	runManager->SetUserInitialization(theGeometry);

	runManager->Initialize();
	
  
	#ifdef G4VIS_USE
  	// Initialize visualization
  	G4VisManager* visManager = new G4VisExecutive;
  	visManager->Initialize();
	#endif

  	// Get the pointer to the User Interface manager
  	G4UImanager* UImanager = G4UImanager::GetUIpointer();

  	if (argc!=1){   // batch mode
    
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
	}
	else{  // interactive mode : define UI session
		#ifdef G4UI_USE
      		G4UIExecutive* ui = new G4UIExecutive(argc, argv);
		#ifdef G4VIS_USE
     // 		UImanager->ApplyCommand("/control/execute vis.mac"); 
		#endif
		ui->SessionStart();
		delete ui;
		#endif
	}

	#ifdef G4VIS_USE
	delete visManager;
	#endif
	delete runManager;

	return 0;
}
