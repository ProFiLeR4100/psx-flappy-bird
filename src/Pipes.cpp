#include <LIBMATH.H>
#include "Pipes.h"
#include "Sprite.h"
#include "SpriteImpl.h"
#include <RAND.H>
#include <PhysicsService.h>
#include "images/img_pipe.tim.h"
#include "images/img_pipe_reversed.tim.h"

Collider Pipes::pipeCollider;

void Pipes::draw() {
	for (int i = 0; i < 5; i++) {
		drawPipe(calculatePipePosition(i), pipes[i]);
	}
}

void Pipes::drawPipe(unsigned int x, unsigned int y) {
	// Top Pipe
	topPipeImage.sprite.x = (short) (x);
	topPipeImage.sprite.y = (short) (y - spaceBetween / 2);
	DisplayService::drawImage(topPipeImage);

	// Bottom Pipe
	bottomPipeImage.sprite.x = (short) (x);
	bottomPipeImage.sprite.y = (short) (y + spaceBetween / 2);
	DisplayService::drawImage(bottomPipeImage);
}

void Pipes::updatePhysics(float fDeltaTime) {
}

bool Pipes::checkCollisionWithBird(Bird *bird) {
	bool inCollisionWithBird = false;
	SpriteImpl collisionCheckPipe;
	collisionCheckPipe.collider = &pipeCollider;
	for (int i = 0; i < 5; i++) {
		printf("%d Position: %d\n", i, calculatePipePosition(i));
		if(calculatePipePosition(i) > DisplayService::SCREEN_WIDTH) continue;

		// Top Pipe
		collisionCheckPipe.image.sprite.w = topPipeImage.sprite.w;
		collisionCheckPipe.image.sprite.h = topPipeImage.sprite.h;
		collisionCheckPipe.image.sprite.mx = topPipeImage.sprite.mx;
		collisionCheckPipe.image.sprite.my = topPipeImage.sprite.my;

		collisionCheckPipe.position.vx = (short) (calculatePipePosition(i));
		collisionCheckPipe.position.vy = (short) (pipes[i] - spaceBetween / 2);
		inCollisionWithBird |= PhysicsService::Intersects2D(&collisionCheckPipe, (Sprite*) bird);

		// Bottom Pipe
		collisionCheckPipe.image.sprite.w = bottomPipeImage.sprite.w;
		collisionCheckPipe.image.sprite.h = bottomPipeImage.sprite.h;
		collisionCheckPipe.image.sprite.mx = bottomPipeImage.sprite.mx;
		collisionCheckPipe.image.sprite.my = bottomPipeImage.sprite.my;

		collisionCheckPipe.position.vx = (short) (calculatePipePosition(i));
		collisionCheckPipe.position.vy = (short) (pipes[i] - spaceBetween / 2);
		inCollisionWithBird |= PhysicsService::Intersects2D(&collisionCheckPipe, (Sprite*) bird);
	}
	return inCollisionWithBird;
}

void Pipes::update(float fDeltaTime) {
	// TODO: Add global vars
	//if (isPlaying) {
	pipesDisposition += 1;
	if (pipesDisposition > bottomPipeImage.sprite.w * 2) {
		pipesDisposition = 0;

		for (int i = 1; i < 5; i++) {
			pipes[i - 1] = pipes[i];
		}

		pipes[4] = randomPipePosition();
	}
	//}
}


int Pipes::randomPipePosition() {
	return (-35 + (75 * _ABS(rand()) / RAND_MAX)) + DisplayService::SCREEN_HEIGHT / 2 - groundSpriteHeight;
}

void Pipes::reset() {
	spaceBetween = 60;

	pipesDisposition = 0;
	pipesDisposition = -1 * DisplayService::SCREEN_WIDTH * 2;

	bottomPipeImage = DisplayService::createImage(img_pipe_tim);
	bottomPipeImage.sprite.mx = (short) (bottomPipeImage.sprite.w / 2);
	bottomPipeImage.sprite.my = 0;

	topPipeImage = DisplayService::createImage(img_pipe_reversed_tim);
	topPipeImage.sprite.mx = (short) (topPipeImage.sprite.w / 2);
	topPipeImage.sprite.my = (short) (topPipeImage.sprite.h);

	for (int i = 0; i < 5; i++) {
		pipes[i] = randomPipePosition();
	}

	pipeCollider.type = COLLIDER_TYPE_RECT;
}

short Pipes::calculatePipePosition(int num) {
	return num * topPipeImage.sprite.w * 2 - ((int) pipesDisposition) - topPipeImage.sprite.mx;
}