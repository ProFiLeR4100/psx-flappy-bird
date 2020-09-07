#include <LIBMATH.H>
#include "AudioService.h"
#include "DisplayService.h"
#include "GamepadService.h"
#include "Bird.h"
#include <STDIO.H>
#include <MathHelper.h>
#include "PhysicsService.h"
#include "images/img_bird_f1.tim.h"
#include "images/img_bird_f2.tim.h"
#include "images/img_bird_f3.tim.h"

CircleCollider Bird::birdCollider;

void Bird::flap() {
	AudioService::audioPlay(SPU_0CH);
	fAcceleration = 0.0f;
	fVelocity = PhysicsService::fGravity / -2.0f;
}

void Bird::draw() {
	Sprite::draw();
}

void Bird::update(float fDeltaTime) {
	if (GamepadService::padCheckPressed(GamepadService::Pad1Cross())
		&& fVelocity >= PhysicsService::fGravity / 20.0f) { // is falling
		flap();
	}

	if(fVelocity < 0) {
		fFrame += 0.25f;
		if (fFrame >= 3.0) {
			fFrame = 0;
		}
	} else {
		fFrame = 1;
	}

	currentFrame = (int) floor(fFrame);

	image = birdFrames[currentFrame];

	image.sprite.rotate = map((int) clamp((int)fVelocity, -50, (int) PhysicsService::fGravity), (int) -50, (int) PhysicsService::fGravity, (int) -45, (int) 45) * ONE;
}

void Bird::updatePhysics(float fDeltaTime) {
	fAcceleration += PhysicsService::fGravity * fWeight * fDeltaTime;

	if (fAcceleration >= PhysicsService::fGravity) {
		fAcceleration = PhysicsService::fGravity;
	}

	fVelocity += fAcceleration * fDeltaTime;
	position.vy += fVelocity * fDeltaTime;
}

void Bird::reset() {
	fWeight = 1.0f;

	position.vy = (short) DisplayService::SCREEN_HEIGHT/2;

	birdFrames[0] = DisplayService::createImage(img_bird_f1_tim);
	birdFrames[1] = DisplayService::createImage(img_bird_f2_tim);
	birdFrames[2] = DisplayService::createImage(img_bird_f3_tim);

	for (int i = 0; i < 3; i++) {
		birdFrames[i].sprite.mx = (short) (birdFrames[i].sprite.w / 2);
		birdFrames[i].sprite.my = (short) (birdFrames[i].sprite.h / 2);
		birdFrames[i].sprite.x = (short) (DisplayService::SCREEN_WIDTH / 2 /*- (birdFrames[i].sprite.w / 2)*/);
		birdFrames[i].sprite.y = (short) (DisplayService::SCREEN_HEIGHT / 2);
	}

	position.vx = (short) (DisplayService::SCREEN_WIDTH / 2);

	birdCollider.type = COLLIDER_TYPE_CIRCLE;
	birdCollider.radius = 15;
	collider = (Collider*) &birdCollider;
}
