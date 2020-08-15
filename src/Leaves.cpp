#include "Leaves.h"
#include "images/img_leaves.tim.h"

void Leaves::draw() {
	for (int i = 0; i < 2; i++) {
		image.sprite.x = (short) floor(i * image.sprite.w - leavesDisposition);
		DisplayService::drawImage(image);
	}
}

void Leaves::updatePhysics(float fDeltaTime) {}

void Leaves::update(float fDeltaTime) {

	leavesDisposition += 0.75;
	if (leavesDisposition > leavesDispositionMax) {
		leavesDisposition = 0;
	}
}

void Leaves::reset() {
	leavesDisposition = 0;
	leavesDispositionMax = 36;

	image = DisplayService::createImage(img_leaves_tim);
	image.sprite.my = image.sprite.h;
	image.sprite.y = (short) (DisplayService::SCREEN_HEIGHT - 30);
}