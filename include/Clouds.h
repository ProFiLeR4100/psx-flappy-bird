#include "DisplayService.h"
#include "Sprite.h"
#include <LIBMATH.H>

#ifndef CLOUDS_H
#define CLOUDS_H

class Clouds : public Sprite {
private:
	float cloudsDisposition;
	short cloudsDispositionMax ;
public:
	virtual void reset();
	virtual void draw();
	virtual void update(float fDeltaTime);
	virtual void updatePhysics(float fDeltaTime);
};

#endif // CLOUDS_H