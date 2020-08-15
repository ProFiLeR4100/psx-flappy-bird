#include "Buildings.h"
#include "images/img_buildings.tim.h"

void Buildings::draw() {
	for (int i = 0; i < 2; i++) {
		image.sprite.x = (short) floor(i * image.sprite.w - buildingsDisposition);
		DisplayService::drawImage(image);
	}
}

void Buildings::updatePhysics(float fDeltaTime) {}

void Buildings::update(float fDeltaTime) {

	buildingsDisposition += 0.5;
	if (buildingsDisposition > buildingsDispositionMax) {
		buildingsDisposition = 0;
	}
}

void Buildings::reset() {
	buildingsDisposition = 0;
	buildingsDispositionMax = 82;

	image = DisplayService::createImage(img_buildings_tim);
	image.sprite.my = image.sprite.h;
	image.sprite.y = (short) (DisplayService::SCREEN_HEIGHT - 30);
}