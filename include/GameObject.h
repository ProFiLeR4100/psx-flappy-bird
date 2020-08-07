#include <LIBGTE.H>

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

struct GameObject {
public:
	virtual void draw() = 0;
	virtual void reset() = 0;
	virtual void update(float fDeltaTime) = 0;
	virtual void updatePhysics(float fDeltaTime) = 0;
};

typedef

#endif // GAME_OBJECT_H