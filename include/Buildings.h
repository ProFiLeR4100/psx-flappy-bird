#include "DisplayService.h"
#include "Sprite.h"
#include <LIBMATH.H>

#ifndef BUILDINGS_H
#define BUILDINGS_H

class Buildings : public Sprite {
private:
	float buildingsDisposition;
	short buildingsDispositionMax;
public:
	virtual void reset();
	virtual void draw();
	virtual void update(float fDeltaTime);
	virtual void updatePhysics(float fDeltaTime);
};

#endif // BUILDINGS_H