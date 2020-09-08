#include "Sprite.h"

#ifndef SPRITE_IMPL_H
#define SPRITE_IMPL_H

class SpriteImpl : public Sprite {
	virtual void reset() {};

	virtual void draw() {};

	virtual void update(float fDeltaTime) {};

	virtual void updatePhysics(float fDeltaTime) {};
};

#endif