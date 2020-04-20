#include "Bird.h"

// https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_FlappyBird.cpp
Bird::Bird() {}

void Bird::flap() {
    if(fVelocity >= fWeight / 10.0f) {
        fAcceleration = 0.0f;
        fVelocity = -fWeight / 4.0f;
    }
}

void Bird::calcPhysics(float fElapsedTime) {
    fAcceleration += fWeight * fElapsedTime;

    if (fAcceleration >= fWeight) {
        fAcceleration = fWeight;
    }

    fVelocity += fAcceleration * fElapsedTime;
    fPosition += fVelocity * fElapsedTime;
}




