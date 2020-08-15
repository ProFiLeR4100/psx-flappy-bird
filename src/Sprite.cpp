#include "Sprite.h"

void Sprite::draw() {
	image.sprite.y = (short) position.vy;
	DisplayService::drawImage(image);
}