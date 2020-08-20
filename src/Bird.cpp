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
	fAcceleration += PhysicsService::fGravity * fDeltaTime;

	if (fAcceleration >= PhysicsService::fGravity) {
		fAcceleration = PhysicsService::fGravity;
	}

	fVelocity += fAcceleration * fDeltaTime;
	position.vy += fVelocity * fDeltaTime;
	printf("Bird a/v/p: %d / %d / %d\n", (int) fAcceleration, (int) fVelocity, (int) position.vy);

//	LINE_F2 line;
//	line.x0 = 0;
//	line.x1 = (short) DisplayService::SCREEN_WIDTH;
//	line.y0 = (short) DisplayService::SCREEN_HEIGHT;
//	line.y1 = (short) DisplayService::SCREEN_HEIGHT;
//	printf("SQ Distance: %d\n", (int) PhysicsService::sqPerpendicuralDistance(line, position));
}

void Bird::reset() {
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
}
