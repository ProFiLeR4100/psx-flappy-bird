//#include "constants.h"
#include "GamepadService.h"
#include "AudioService.h"
#include "DisplayService.h"
#include <LIBSPU.H>
#include <LIBGTE.H>
#include <ColorHelper.h>
#include <LIBMATH.H>
#include <STDIO.H>
#include <KERNEL.H>
#include <LIBAPI.H>
#include <RAND.H>
#include <LIBGS.H>
#include "Buildings.h"
#include "Clouds.h"
#include "Leaves.h"
#include "Ground.h"
#include "GameObjectService.h"
#include "CDService.h"
#include "sounds/jump.h"
#include "sounds/passed.h"
#include "images/img_logo.tim.h"
#include "images/img_game_over.tim.h"
#include "images/img_pipe.tim.h"
#include "images/img_pipe_reversed.tim.h"
#include "PhysicsService.h"
#include "Bird.h"

void initialize();

void update();

void draw();

/** Parallax zone */
Buildings buildings;
Clouds clouds;
Leaves leaves;
Ground ground;
//Image buildings;
//Image clouds;
//Image leaves;
/** Parallax zone end */

Image logo;
Image gameOver;
//Image ground;
Image pipe;
Image pipeReversed;
//Image restart;
float frame = 0;


short pipeDisplacement = 0;
int pipes[5];
bool isGameOver = false;
bool isPlaying = true;
int coinCount = 0;
Bird bird;
//List<int> intList;

int main() {
	initialize();
	while (1) {
		update();
		DisplayService::clearDisplay();
		draw();
		DisplayService::display();
	}
}

int randomPipePosition() {
	return (-35 + (75 * _ABS(rand()) / RAND_MAX)) + DisplayService::SCREEN_HEIGHT / 2 - ground.image.sprite.h;
}

void resetGame() {
	coinCount = 0;
	ground.reset();
	clouds.reset();
	buildings.reset();
	leaves.reset();
	pipeDisplacement = 0;
	bird.reset();

	pipeDisplacement = -1 * DisplayService::SCREEN_WIDTH * 2;

	for (int i = 0; i < 5; i++) {
		pipes[i] = randomPipePosition();
	}
}

void initialize() {
	DisplayService::initialize();
	GamepadService::initialize();
	AudioService::initialize();

	CDService::open();
	CDService::close();

	AudioService::audioTransferVagToSPU(&jump[0], jump_size, SPU_0CH, 0xffff);
	AudioService::audioTransferVagToSPU(&passed[0], passed_size, SPU_1CH, 0x0aff);

	AudioService::setVolume(SPU_1CH, 0);

	logo = DisplayService::createImage(img_logo_tim);
	logo.sprite.mx = (short) (logo.sprite.w / 2);
	logo.sprite.my = (short) (logo.sprite.h / 2);
	logo.sprite.x = (short) (DisplayService::SCREEN_WIDTH / 2);
	logo.sprite.y = (short) (DisplayService::SCREEN_HEIGHT * 0.25);

	gameOver = DisplayService::createImage(img_game_over_tim);
	gameOver.sprite.mx = (short) (gameOver.sprite.w / 2);
	gameOver.sprite.my = (short) (gameOver.sprite.h / 2);
	gameOver.sprite.x = (short) (DisplayService::SCREEN_WIDTH / 2);
	gameOver.sprite.y = (short) (DisplayService::SCREEN_HEIGHT / 2);


/** Pipes */
	pipe = DisplayService::createImage(img_pipe_tim);
	pipe.sprite.mx = (short) (pipe.sprite.w / 2);
	pipe.sprite.my = 0;

	pipeReversed = DisplayService::createImage(img_pipe_reversed_tim);
	pipeReversed.sprite.mx = (short) (pipeReversed.sprite.w / 2);
	pipeReversed.sprite.my = pipeReversed.sprite.h;
/** Pipes end*/

	if (!GameObjectService::enableGameObject(&ground)) {
		printf("Ground is not enabled.");
	}

//	drawPipes();

	if (!GameObjectService::enableGameObject(&bird)) {
		printf("Bird is not enabled.");
	}

	if (!GameObjectService::enableGameObject(&leaves)) {
		printf("Leaves is not enabled.");
	}

	if (!GameObjectService::enableGameObject(&buildings)) {
		printf("Buildings is not enabled.");
	}

	if (!GameObjectService::enableGameObject(&clouds)) {
		printf("Clouds is not enabled.");
	}

	resetGame();

	DisplayService::setBackgroundColor(ColorHelper::fromRGB(112, 197, 206));
}

short getPipePosition(int num) {
	return num * pipe.sprite.w * 2 - pipeDisplacement - pipe.sprite.mx;
}

void BirdUpdate() {
	// physics and control
	float fElapsedTime = 0.016f; // 60Hz => 1 sec / 60Hz = 0.01(6)

	if (isPlaying) {
		GameObjectService::update(fElapsedTime);
		GameObjectService::updatePhysics(fElapsedTime);

//		for (int i = 0; i < 5; i++) {
//			if (getPipePosition(i) == floor(bird.position.vx + (bird.birdFrames[bird.currentFrame].sprite.w / 2)) ) {
//				AudioService::audioPlay(SPU_1CH);
//				coinCount++;
//			}
//		}
	}
}

void PipesUpdate() {
	if (isPlaying) {
		pipeDisplacement += 1;
		if (pipeDisplacement > pipe.sprite.w * 2) {
			pipeDisplacement = 0;

			for (int i = 1; i < 5; i++) {
				pipes[i - 1] = pipes[i];
			}

			pipes[4] = randomPipePosition();
		}
	}
}

void update() {
	GamepadService::padUpdate();
	BirdUpdate();

	PipesUpdate();
}

void drawPipe(unsigned int x, unsigned int y, short spaceBetween) {
	// Top Pipe
	pipeReversed.sprite.x = (short) (x);
	pipeReversed.sprite.y = (short) (y - spaceBetween / 2);
	DisplayService::drawImage(pipeReversed);
	// Bottom Pipe
	pipe.sprite.x = (short) (x);
	pipe.sprite.y = (short) (y + spaceBetween / 2);
	DisplayService::drawImage(pipe);
}

void drawPipes() {
	for (int i = 0; i < 5; i++) {
		drawPipe(getPipePosition(i), pipes[i], 60);
	}
}

char scoreText[30];

void drawScore() {

}

void draw() {
	if (isGameOver) {
		DisplayService::drawImage(gameOver);
	}

	if (!isPlaying) {
		DisplayService::drawImage(logo);
	}

	sprintf(&scoreText[0], "%d", coinCount);
	// TOP
	drawPipes();
	GameObjectService::draw();
	// BOTTOM
}


