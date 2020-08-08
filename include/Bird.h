#include "GameObject.h"
#include "Image.h"
#include "Vector2F.h"

#ifndef BIRD_H
#define BIRD_H

struct Bird : GameObject {
	void flap();


	virtual void reset();
	virtual void draw();
	virtual void update(float fDeltaTime);
	virtual void updatePhysics(float fDeltaTime);

	float fVelocity;
	float fAcceleration;
	float fWeight;
	Image birdFrames[3];
	float fFrame;
	short currentFrame;
	Vector2F position;
};

#endif // BIRD_H