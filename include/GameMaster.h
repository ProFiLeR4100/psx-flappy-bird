#include "Sprite.h"
#include "GameObject.h"
#include "GameState.h"

#ifndef GAME_MASTER_H
#define GAME_MASTER_H

class GameMaster : public GameObject {
public:

	virtual void reset();

	virtual void draw();

	virtual void update(float fDeltaTime);

	virtual void updatePhysics(float fDeltaTime);

	GameState gameState;

	Sprite *ground;
	Sprite *bird;
	// TODO: add pipes collision calculation
	Sprite *pipes;
};

#endif // GAME_MASTER_H