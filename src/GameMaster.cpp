#include <STDIO.H>
#include "GameMaster.h"
#include "PhysicsService.h"

void GameMaster::draw() {}

void GameMaster::reset() {}

void GameMaster::update(float fDeltaTime) {}

void GameMaster::updatePhysics(float fDeltaTime) {
	if (ground->checkCollisionWIthBird(bird)) {
		printf("YAY! Ground Collision found!!!\n");
	} else {
		printf("No Ground Collision!\n");
	}

// TODO: add collision to pipes
	if(pipes->checkCollisionWithBird(bird)) {
		printf("YAY! Pipe Collision found!!!\n");
	} else {
		printf("No Pipe Collision!\n");
	}
}