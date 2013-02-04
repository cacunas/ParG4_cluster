#ifndef LYSOHit_h
#define LYSOHit_h 1

//MSH_include_begin
#include "MarshaledG4String.h"
//MSH_include_end


#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"




//MSH_BEGIN
class LYSOHit : public G4VHit{

public:
	LYSOHit();
	LYSOHit(G4double, G4ThreeVector);
	~LYSOHit();
	
	inline void* operator new(size_t);
	inline void  operator delete(void*);

	void Draw();
	void Print();	

	void setEnergy(G4double Energy)	{energy = Energy;};
	G4double getEnergy() const	{return energy;  };
	void setPos(G4ThreeVector Pos)  {pos = Pos; };
	G4ThreeVector getPos() const		{return pos;};

private:
	G4double energy;
	G4ThreeVector pos;
};
//MSH_END

typedef G4THitsCollection<LYSOHit> LYSOHitsCollection;
extern G4Allocator<LYSOHit> LYSOHitAllocator;

inline void* LYSOHit::operator new(size_t){

	void* hit;
	hit = (void*)LYSOHitAllocator.MallocSingle();
	return hit;
}

inline void LYSOHit::operator delete(void* hit){

	LYSOHitAllocator.FreeSingle((LYSOHit*)hit);
}
#endif
