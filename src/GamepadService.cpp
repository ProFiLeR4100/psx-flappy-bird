#include "GamepadService.h"
#include <STDLIB.H>
#include <LIBETC.H>

int GamepadService::SysPad = 0;
int GamepadService::SysPadT = 0;

void GamepadService::initialize() {
    PadInit(0);
}

void GamepadService::padReset() {
    GamepadService::SysPad = 0;
    GamepadService::SysPadT = 0;
}

void GamepadService::padUpdate() {
    int pad = PadRead(0);
    GamepadService::SysPadT = pad & (pad ^ GamepadService::SysPad);
    GamepadService::SysPad = pad;
}


