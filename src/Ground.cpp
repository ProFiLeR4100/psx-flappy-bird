#include <Bird.h>
#include <PhysicsService.h>
#include "Ground.h"
#include "images/img_ground.tim.h"

Collider Ground::groundCollider;

void Ground::draw() {
	for (int i = 0; i < 2; i++) {
		image.sprite.x = (short) floor(i * image.sprite.w - groundDisposition);
		DisplayService::drawImage(image);
	}
}

void Ground::updatePhysics(float fDeltaTime) {}

void Ground::update(float fDeltaTime) {

	groundDisposition += 1;
	if (groundDisposition > groundDispositionMax) {
		groundDisposition = 0;
	}

	position.vx = groundDisposition;
	position.vy = image.sprite.y;
}

void Ground::reset() {
	groundDisposition = 0;
	groundDispositionMax = 13;

	image = DisplayService::createImage(img_ground_tim);
	image.sprite.mx = 0;
	image.sprite.my = image.sprite.h;
	image.sprite.y = (short) (DisplayService::SCREEN_HEIGHT);
	image.sprite.x = 0;

	collider = (Collider*) &groundCollider;
	groundCollider.type = COLLIDER_TYPE_RECT;
}

bool Ground::checkCollisionWIthBird(Bird* bird) {
	return PhysicsService::Intersects2D((Sprite *) this, (Sprite*) bird);
}
