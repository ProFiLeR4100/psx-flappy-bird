#include "DisplayService.h"
#include "Sprite.h"
#include "Bird.h"
#include "Collider.h"
#include <LIBMATH.H>

#ifndef PIPES_H
#define PIPES_H

class Pipes : public GameObject {
private:
	float pipesDisposition;
	Image bottomPipeImage;
	Image topPipeImage;
	int pipes[5];

	short calculatePipePosition(int num);

	void drawPipe(unsigned int x, unsigned int y);

	int randomPipePosition();

	static Collider pipeCollider;

public:
	Collider* collider;
	virtual void reset();

	virtual void draw();

	virtual void update(float fDeltaTime);

	virtual void updatePhysics(float fDeltaTime);

	short groundSpriteHeight; //ground.image.sprite.h
	bool checkCollisionWithBird(Bird *Bird);

	short spaceBetween;
};

#endif // PIPES_H