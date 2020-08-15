#include "Ground.h"
#include "images/img_ground.tim.h"

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
}

void Ground::reset() {
	groundDisposition = 0;
	groundDispositionMax = 13;


	image = DisplayService::createImage(img_ground_tim);
	image.sprite.mx = 0;
	image.sprite.my = image.sprite.h;
	image.sprite.y = (short) (DisplayService::SCREEN_HEIGHT);
	image.sprite.x = 0;
}