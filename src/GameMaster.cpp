#include <STDIO.H>
#include "GameMaster.h"
#include "PhysicsService.h"

void GameMaster::draw() {}

void GameMaster::reset() {}

void GameMaster::update(float fDeltaTime) {}

void GameMaster::updatePhysics(float fDeltaTime) {
	if (PhysicsService::Intersects2D(ground, bird)) {
		printf("YAY! Collision found!!!\n");
	} else {
		printf("No Collision!\n");
	}
}