#include "Clouds.h"
#include "images/img_clouds.tim.h"

void Clouds::draw() {
	for (int i = 0; i < 2; i++) {
		image.sprite.x = (short) floor(i * image.sprite.w - cloudsDisposition);
		DisplayService::drawImage(image);
	}
}

void Clouds::updatePhysics(float fDeltaTime) {}

void Clouds::update(float fDeltaTime) {

	cloudsDisposition += 0.25;
	if (cloudsDisposition > cloudsDispositionMax) {
		cloudsDisposition = 0;
	}
}

void Clouds::reset() {
	cloudsDisposition = 0;
	cloudsDispositionMax = 80;

	image = DisplayService::createImage(img_clouds_tim);
	image.sprite.my = image.sprite.h;
	image.sprite.y = (short) (DisplayService::SCREEN_HEIGHT - 30);
}