#include <AudioService.h>
#include <DisplayService.h>
#include <GameObject.h>
#include <LIBMATH.H>
#include "images/img_bird_f1.tim.h"
#include "images/img_bird_f2.tim.h"
#include "images/img_bird_f3.tim.h"
#include "Bird.h"

// https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_FlappyBird.cpp
Bird::Bird() : fVelocity(), fAcceleration(), fWeight(), birdFrames(), fFrame() {
	birdFrames[0] = DisplayService::createImage(img_bird_f1_tim);
	birdFrames[1] = DisplayService::createImage(img_bird_f2_tim);
	birdFrames[2] = DisplayService::createImage(img_bird_f3_tim);
}

void Bird::flap() {
}

void Bird::draw() {
	DisplayService::drawImage(birdFrames[(int) floor(fFrame)]);
}

void Bird::update(float fDeltaTime) {
	fFrame += 0.25f;
	if (fFrame >= 3.0) {
		fFrame = 0;
	}
}

void Bird::updatePhysics(float fDeltaTime) {
//	&GameObject::position;
//	DVECTOR* dvector = static_cast<DVECTOR *>(&GameObject::position);
//	Physics::updatePosition(&fAcceleration, &fVelocity, &fWeight, , fElapsedTime);
}
