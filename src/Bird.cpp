#include <AudioService.h>
#include <DisplayService.h>
#include <LIBMATH.H>
#include "Bird.h"
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
	for (int i = 0; i < 3; i++) {
		birdFrames[i].sprite.y = (short) position.vy;
	}

	DisplayService::drawImage(birdFrames[(int) floor(fFrame)]);
}

void Bird::update(float fDeltaTime) {
	fFrame += 0.25f;
	if (fFrame >= 3.0) {
		fFrame = 0;
	}
}

void Bird::updatePhysics(float fDeltaTime) {
//	if (fAcceleration >= fGravity) {
//		fAcceleration = fGravity;
//	}
//
//	fBirdVelocity += fBirdAcceleration * fElapsedTime;
//	fBirdPosition += fBirdVelocity * fElapsedTime;
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
