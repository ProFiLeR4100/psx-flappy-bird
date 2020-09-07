#include "DisplayService.h"
#include "Sprite.h"
#include <LIBMATH.H>

#ifndef GROUND_H
#define GROUND_H

class Ground : public Sprite {
private:
	float groundDisposition;
	short groundDispositionMax;
	static Collider groundCollider;
public:
	virtual void reset();

	virtual void draw();

	virtual void update(float fDeltaTime);

	virtual void updatePhysics(float fDeltaTime);
};

#endif // GROUND_H