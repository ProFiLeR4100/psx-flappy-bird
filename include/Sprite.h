#include "GameObject.h"
#include "Image.h"
#include "Vector2F.h"
#include "DisplayService.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite : public GameObject {
public:
	virtual void reset();
	virtual void draw();
	virtual void update(float fDeltaTime);
	virtual void updatePhysics(float fDeltaTime);

	Image image;
	Vector2F position;
};

#endif // SPRITE_H