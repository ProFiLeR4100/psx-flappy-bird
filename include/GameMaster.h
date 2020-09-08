#include "Sprite.h"
#include "Ground.h"
#include "Bird.h"
#include "Pipes.h"
#include "LIBGS.H"
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

	Ground *ground;
	Bird *bird;
	// TODO: add pipes collision calculation
	Pipes *pipes;
};

#endif // GAME_MASTER_H