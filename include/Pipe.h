#include "DisplayService.h"
#include "Sprite.h"
#include <LIBMATH.H>

#ifndef PIPE_H
#define PIPE_H

class Pipe : public Sprite {
public:
	virtual void reset();
	virtual void draw();
	virtual void update(float fDeltaTime);
	virtual void updatePhysics(float fDeltaTime);
};

#endif // PIPE_H