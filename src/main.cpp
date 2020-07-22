//#include "constants.h"
#include "GamepadService.h"
#include "AudioService.h"
#include "DisplayService.h"
#include <LIBSPU.H>
#include <LIBGTE.H>
#include <ColorHelper.h>
#include <LIBMATH.H>
#include <KERNEL.H>
#include <LIBAPI.H>
#include <RAND.H>
#include <LIBGS.H>
#include <CDService.h>
#include <sounds/jump.h>
#include <sounds/passed.h>
#include <images/img_buildings.tim.h>
#include <images/img_clouds.tim.h>
#include <images/img_leaves.tim.h>
#include <images/img_logo.tim.h>
#include <images/img_game_over.tim.h>
#include <images/img_ground.tim.h>
#include <images/img_pipe.tim.h>
#include <images/img_pipe_reversed.tim.h>
#include <images/img_bird_f1.tim.h>
#include <images/img_bird_f2.tim.h>
#include <images/img_bird_f3.tim.h>

void initialize();

void update();

void draw();

/** Parallax zone */
Image buildings;
Image clouds;
Image leaves;
/** Parallax zone end */

Image logo;
Image gameOver;
Image ground;
Image pipe;
Image pipeReversed;
//Image restart;
Image birdFrames[3];
float frame = 0;
float groundDisposition = 0;
short groundDispositionMax = 13;
float cloudsDisposition = 0;
short cloudsDispositionMax = 80;
float buildingsDisposition = 0;
short buildingsDispositionMax = 82;
float leavesDisposition = 0;
short leavesDispositionMax = 36;
short pipeDisplacement = 0;
float fGravity = 100.0f;
float fBirdPosition = 0;
float fBirdVelocity = 0;
float fBirdAcceleration = 0;
int pipes[5];
bool isGameOver = false;
bool isPlaying = true;
int coinCount = 0;

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
    return (-35 + (75 * _ABS(rand()) / RAND_MAX)) + DisplayService::SCREEN_HEIGHT / 2 - ground.sprite.h;
}

void resetGame() {
    coinCount = 0;
    groundDisposition = 0;
    cloudsDisposition = 0;
    buildingsDisposition = 0;
    leavesDisposition = 0;
    pipeDisplacement = 0;
    fBirdVelocity = 0;
    fBirdAcceleration = 0;

    fBirdPosition = (short) (DisplayService::SCREEN_HEIGHT / 2);
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

/** Parallax zone */
    buildings = DisplayService::createImage(img_buildings_tim);
    buildings.sprite.my = buildings.sprite.h;
    buildings.sprite.y = (short) (DisplayService::SCREEN_HEIGHT - 30);
    clouds = DisplayService::createImage(img_clouds_tim);
    clouds.sprite.my = clouds.sprite.h;
    clouds.sprite.y = (short) (DisplayService::SCREEN_HEIGHT - 30);
    leaves = DisplayService::createImage(img_leaves_tim);
    leaves.sprite.my = leaves.sprite.h;
    leaves.sprite.y = (short) (DisplayService::SCREEN_HEIGHT - 30);
/** Parallax zone end */

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

    ground = DisplayService::createImage(img_ground_tim);
    ground.sprite.mx = 0;
    ground.sprite.my = ground.sprite.h;
    ground.sprite.y = (short) (DisplayService::SCREEN_HEIGHT);
    ground.sprite.x = 0;

/** Pipes */
    pipe = DisplayService::createImage(img_pipe_tim);
    pipe.sprite.mx = (short) (pipe.sprite.w / 2);
    pipe.sprite.my = 0;

    pipeReversed = DisplayService::createImage(img_pipe_reversed_tim);
    pipeReversed.sprite.mx = (short) (pipeReversed.sprite.w / 2);
    pipeReversed.sprite.my = pipeReversed.sprite.h;
/** Pipes end*/

    birdFrames[0] = DisplayService::createImage(img_bird_f1_tim);
    birdFrames[1] = DisplayService::createImage(img_bird_f2_tim);
    birdFrames[2] = DisplayService::createImage(img_bird_f3_tim);

    for (int i = 0; i < 3; i++) {
        birdFrames[i].sprite.mx = 0;
        birdFrames[i].sprite.my = (short) (birdFrames[i].sprite.h / 2);
        birdFrames[i].sprite.x = (short) (DisplayService::SCREEN_WIDTH / 2 - (birdFrames[i].sprite.w / 2));
        birdFrames[i].sprite.y = (short) (DisplayService::SCREEN_HEIGHT / 2);
    }

    resetGame();

    DisplayService::setBackgroundColor(ColorHelper::fromRGB(112, 197, 206));
}

short getPipePosition(int num) {
    return num * pipe.sprite.w * 2 - pipeDisplacement - pipe.sprite.mx;
}

void BirdUpdate() {
    // Animation
    frame += 0.25f;
    if (frame >= 3.0) {
        frame = 0;
    }

    // physics and control
    float fElapsedTime = 0.016f; // 60Hz => 1 sec / 60Hz = 0.01(6)

    if(isPlaying) {
        if (GamepadService::padCheckPressed(GamepadService::Pad1Cross()) && fBirdVelocity >= fGravity / 20.0f) {
            AudioService::audioPlay(SPU_0CH);
            fBirdAcceleration = 0.0f;
            fBirdVelocity = -fGravity / 2.0f;
        } else {
            fBirdAcceleration += fGravity * fElapsedTime;
        }

        if (fBirdAcceleration >= fGravity) {
            fBirdAcceleration = fGravity;
        }

        fBirdVelocity += fBirdAcceleration * fElapsedTime;
        fBirdPosition += fBirdVelocity * fElapsedTime;

        // set Position

        for (int i = 0; i < 3; i++) {
            birdFrames[i].sprite.y = (short) fBirdPosition;
        }

        for (int i = 0; i < 5; i++) {
            if (getPipePosition(i) == floor(birdFrames[0].sprite.x + (birdFrames[0].sprite.w / 2)) ) {
                AudioService::audioPlay(SPU_1CH);
                coinCount++;
            }
        }
    }
}

void PipesUpdate() {
    if(isPlaying) {
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

    groundDisposition += 1;
    if (groundDisposition > groundDispositionMax) {
        groundDisposition = 0;
    }

    cloudsDisposition += 0.25;
    if (cloudsDisposition > cloudsDispositionMax) {
        cloudsDisposition = 0;
    }

    buildingsDisposition += 0.5;
    if (buildingsDisposition > buildingsDispositionMax) {
        buildingsDisposition = 0;
    }

    leavesDisposition += 0.75;
    if (leavesDisposition > leavesDispositionMax) {
        leavesDisposition = 0;
    }
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

void drawGround() {
    for (int i = 0; i < 2; i++) {
        ground.sprite.x = (short) floor(i * ground.sprite.w - groundDisposition);
        DisplayService::drawImage(ground);
    }
}

void drawBuildings() {
    for (int i = 0; i < 2; i++) {
        buildings.sprite.x = (short) floor(i * buildings.sprite.w - buildingsDisposition);
        DisplayService::drawImage(buildings);
    }
}

void drawClouds() {
    for (int i = 0; i < 2; i++) {
        clouds.sprite.x = (short) floor(i * clouds.sprite.w - cloudsDisposition);
        DisplayService::drawImage(clouds);
    }
}

void drawLeaves() {
    for (int i = 0; i < 2; i++) {
        leaves.sprite.x = (short) floor(i * leaves.sprite.w - leavesDisposition);
        DisplayService::drawImage(leaves);
    }
}

char scoreText[30];

void drawScore() {

}

void draw() {
    if(isGameOver) {
        DisplayService::drawImage(gameOver);
    }

    if(!isPlaying) {
        DisplayService::drawImage(logo);
    }

    sprintf(&scoreText[0], "%d", coinCount);

    drawGround();
    drawPipes();
    DisplayService::drawImage(birdFrames[(int) floor(frame)]);
    drawLeaves();
    drawBuildings();
    drawClouds();
}


