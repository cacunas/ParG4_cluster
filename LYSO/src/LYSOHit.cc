#include "LYSOHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4Allocator<LYSOHit> LYSOHitAllocator;

LYSOHit::LYSOHit()
	: G4VHit(),
	  energy(0),
	  pos(G4ThreeVector())
{}

LYSOHit::LYSOHit(G4double Energy, G4ThreeVector Pos){

	energy	= Energy;
	pos	= Pos;
}

LYSOHit::~LYSOHit()
{}

void LYSOHit::Draw(){

	G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
	if(pVVisManager){
		G4Circle circle(pos);
		circle.SetScreenSize(2.);
		circle.SetFillStyle(G4Circle::filled);
		G4Colour colour(1.,1.,0.);
		G4VisAttributes attribs(colour);
		circle.SetVisAttributes(attribs);
		pVVisManager->Draw(circle);
  	}
}

void LYSOHit::Print()
{
	G4cout
	<<"Energy: "<<std::setw(7) << G4BestUnit(energy,"Energy")
      	<<"\tPosition: "<< std::setw(7) << G4BestUnit( pos,"Length")
	<<G4endl;
}
