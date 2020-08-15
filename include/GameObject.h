#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject {
public:
	virtual void reset() {};
	virtual void draw() {};
	virtual void update(float fDeltaTime) {};
	virtual void updatePhysics(float fDeltaTime) {};
};

#endif // GAME_OBJECT_H