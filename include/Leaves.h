#include "DisplayService.h"
#include "Sprite.h"
#include <LIBMATH.H>

#ifndef LEAVES_H
#define LEAVES_H

class Leaves : public Sprite {
private:
	float leavesDisposition;
	short leavesDispositionMax;
public:
	virtual void reset();
	virtual void draw();
	virtual void update(float fDeltaTime);
	virtual void updatePhysics(float fDeltaTime);
};

#endif // LEAVES_H