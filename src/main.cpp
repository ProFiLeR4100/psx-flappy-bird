//#include "constants.h"
#include "GamepadService.h"
#include "AudioService.h"
#include "DisplayService.h"
#include "Bird.h"
#include "sounds/hpup.h"
#include "sounds/crate.h"
#include <LIBSPU.H>
#include <LIBGTE.H>
#include <ColorHelper.h>
#include <images.h>
#include <LIBMATH.H>

void initialize();
void update();
void draw();

Image bird_frames[3];
float frame = 0;
int rot = 0;
int main() {
    initialize();
    while(1) {
        update();
        DisplayService::clearDisplay();
        draw();
        DisplayService::display();
    }
}

void initialize() {
    DisplayService::initialize();
    GamepadService::initialize();
    AudioService::initialize();

    AudioService::audioTransferVagToSPU(&hpup[0], hpup_size, SPU_0CH);
    AudioService::audioTransferVagToSPU(&crate[0], crate_size, SPU_1CH);
    AudioService::audioPlay(SPU_0CH);
    AudioService::audioPlay(SPU_1CH);

    bird_frames[0] = DisplayService::createImage(img_bird_f1);
    bird_frames[1] = DisplayService::createImage(img_bird_f2);
    bird_frames[2] = DisplayService::createImage(img_bird_f3);

    for(int i = 0; i < 3; i++) {
        bird_frames[i].sprite.mx = 33;
        bird_frames[i].sprite.my = 32;
        bird_frames[i].sprite.x = 320 / 2 + i * 32;
        bird_frames[i].sprite.y = 240 / 2;
    }


    DisplayService::setBackgroundColor(ColorHelper::fromRGB(255,255,255));
}

void update() {
    GamepadService::padUpdate();
}

void draw() {
    DisplayService::drawImage(bird_frames[0]);
    DisplayService::drawImage(bird_frames[1]);
    DisplayService::drawImage(bird_frames[2]);
}