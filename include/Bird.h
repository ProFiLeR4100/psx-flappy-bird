#include "GameObject.h"
#include "Image.h"
#include "Sprite.h"
#include <STDIO.H>
#include "Vector2F.h"
#include <LIBGS.H>
#include <LIBGPU.H>
#include "CircleCollider.h"
#include "ColliderType.h"

#ifndef BIRD_H
#define BIRD_H

class Bird : public Sprite {
public:
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

private:
	static CircleCollider birdCollider;
};

#endif // BIRD_H