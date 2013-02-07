ParG4_cluster
=============

Multi threaded code for geant4 simulations. For being used over the cluster.

This repo contains the source code that implements the simulation of a simple 
setup of a LYSO scintillator crystal on a cluster, using multithreading to 
improve the performance of several events over a reduced amount of time.

The software used for this project and their respective versions are:

-ROOT : Version   5.34/02
-GEANT4: Version   9.5.1
-TOP-C: Version 2.5.2
-GCC: Version 4.4.6
-MARSHALGEN: Version 1.0

The original LYSO source file structure was like this:

+- LYSO/
  +- src/
    +- LYSOEventAction.cc
    +- LYSOGeometry.cc
    +- LYSOHit.cc
    +- LYSOPhysicsList.cc
    +- LYSOPrimaryGeneratorAction.cc
    +- LYSORunAction.cc
    +- LYSOSD.cc
  +- include/
    +- LYSOEventAction.hh
    +- LYSOGeometry.hh
    +- LYSOHit.hh
    +- LYSOPhysicsList.hh
    +- LYSOPrimaryGeneratorAction.hh
    +- LYSORunAction.hh
    +- LYSOSD.hh
  +- CMakeLists.txt
  +- vis.mac
  +- LYSO.cc
  
Note that in the original version the compilation of the project were made
with CMake, so there were no need for a Makefile.

Now, the multithreaded version file structure is like the following:

+- LYSO/
  +- src/
    +- G4MTGetTid.cc (*)
    +- LYSOEventAction.cc
    +- LYSOGeometry.cc
    +- LYSOHit.cc
    +- LYSOPhysicsList.cc
    +- LYSOPrimaryGeneratorAction.cc
    +- LYSORunAction.cc (*)
    +- LYSOSD.cc
    +- ParRunManager.cc (*)
  +- include/
    +- G4MTGetTid.hh (*)
    +- GNUmakefile (*)
    +- LYSOEventAction.hh
    +- LYSOGeometry.hh
    +- LYSOHit.hh (*)
    +- LYSOPhysicsList.hh
    +- LYSOPrimaryGeneratorAction.hh
    +- LYSORunAction.hh 
    +- LYSOSD.hh
    +- LYSOHit.msh (*)
    +- MarshaledG4HCofThisEvent.h (*)
    +- MarshaledG4String.h (*)
    +- MarshaledG4THitsCollection.h (*)
    +- MarshaledG4VHitsCollection.h (*)
    +- MarshaledLYSOHit.h (*)
    +- MarshaledObj.h (*)
    +- ParRunManager.hh (*)
  +- AnnotatedFiles/ (*)
    +- G4HCofThisEvent.hh
    +- G4String.hh
    +- G4THitsCollection.hh
    +- G4VHitsCollection.hh
    +- G4HCofThisEvent.msh
    +- G4String.msh
    +- G4THitsCollection.msh
    +- G4VHitsCollection.msh
    +- MarshaledG4HCofThisEvent.h
    +- MarshaledG4String.h
    +- MarshaledG4THitsCollection.h
    +- MarshaledG4VHitsCollection.h
  +- GNUmakefile (*)
  +- ParGNUmakefile (*)
  +- procgroup (*)
  +- vis.mac
  +- LYSO.cc (*)
  +- ParTopC.icc (*)
  
The differences witj the original version are the ones marked with the '(*)'
(the AnnotatedFiles and its content its whole new, so I just marked the directory 
instead of all the files in it). The explanation for these differences will be explained below.

