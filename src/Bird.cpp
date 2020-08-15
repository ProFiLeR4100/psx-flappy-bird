#include <LIBMATH.H>
#include "AudioService.h"
#include "DisplayService.h"
#include "GamepadService.h"
#include "Bird.h"
#include <STDIO.H>
#include "PhysicsService.h"
#include "images/img_bird_f1.tim.h"
#include "images/img_bird_f2.tim.h"
#include "images/img_bird_f3.tim.h"


void Bird::flap() {
	AudioService::audioPlay(SPU_0CH);
	fAcceleration = 0.0f;
	fVelocity = PhysicsService::fGravity / -2.0f;
}

void Bird::draw() {
	Sprite::draw();
}

void Bird::update(float fDeltaTime) {
//	if (GamepadService::padCheckPressed(GamepadService::Pad1Cross()) && fBirdVelocity >= fGravity / 20.0f) {
//		AudioService::audioPlay(SPU_0CH);
//		fBirdAcceleration = 0.0f;
//		fBirdVelocity = -fGravity / 2.0f;
//	} else {
//		fBirdAcceleration += fGravity * fElapsedTime;
//	}
//
//	if (fBirdAcceleration >= fGravity) {
//		fBirdAcceleration = fGravity;
//	}
//
//	fBirdVelocity += fBirdAcceleration * fElapsedTime;
//	fBirdPosition += fBirdVelocity * fElapsedTime;

//	Sprite::draw();

	if (GamepadService::padCheckPressed(GamepadService::Pad1Cross())
		&& fVelocity >= PhysicsService::fGravity / 20.0f) { // is falling
		flap();
	}

	fFrame += 0.25f;
	if (fFrame >= 3.0) {
		fFrame = 0;
	}
	currentFrame = (int) floor(fFrame);

	image = birdFrames[currentFrame];
}

void Bird::updatePhysics(float fDeltaTime) {
	fAcceleration += PhysicsService::fGravity * fDeltaTime;

	if (fAcceleration >= PhysicsService::fGravity) {
		fAcceleration = PhysicsService::fGravity;
	}


	fVelocity += fAcceleration * fDeltaTime;
	position.vy += fVelocity * fDeltaTime;
	printf("Bird a/v/p: %d / %d / %d\n", (int) fAcceleration, (int) fVelocity, (int) position.vy);
}

void Bird::reset() {
	birdFrames[0] = DisplayService::createImage(img_bird_f1_tim);
	birdFrames[1] = DisplayService::createImage(img_bird_f2_tim);
	birdFrames[2] = DisplayService::createImage(img_bird_f3_tim);

	for (int i = 0; i < 3; i++) {
		birdFrames[i].sprite.mx = 0;
		birdFrames[i].sprite.my = (short) (birdFrames[i].sprite.h / 2);
		birdFrames[i].sprite.x = (short) (DisplayService::SCREEN_WIDTH / 2 - (birdFrames[i].sprite.w / 2));
		birdFrames[i].sprite.y = (short) (DisplayService::SCREEN_HEIGHT / 2);
	}

	position.vx = (short) (DisplayService::SCREEN_WIDTH / 2);
}
