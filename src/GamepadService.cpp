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


int GamepadService::padCheck(int pad) {
	return (GamepadService::SysPad & (pad));
}

int GamepadService::padCheckPressed(int pad) {
	return (GamepadService::SysPadT & (pad));
}

int GamepadService::Pad1Up() {
	return _PAD(0, PADLup);
}

int GamepadService::Pad1Down() {
	return _PAD(0, PADLdown);
}

int GamepadService::Pad1Left() {
	return _PAD(0, PADLleft);
}

int GamepadService::Pad1Right() {
	return _PAD(0, PADLright);
}

int GamepadService::Pad1Triangle() {
	return _PAD(0, PADRup);
}

int GamepadService::Pad1Cross() {
	return _PAD(0, PADRdown);
}

int GamepadService::Pad1Square() {
	return _PAD(0, PADRleft);
}

int GamepadService::Pad1Circle() {
	return _PAD(0, PADRright);
}

int GamepadService::Pad1L1() {
	return _PAD(0, PADL1);
}

int GamepadService::Pad1L2() {
	return _PAD(0, PADL2);
}

int GamepadService::Pad1R1() {
	return _PAD(0, PADR1);
}

int GamepadService::Pad1R2() {
	return _PAD(0, PADR2);
}

int GamepadService::Pad1Start() {
	return _PAD(0, PADstart);
}

int GamepadService::Pad1Select() {
	return _PAD(0, PADselect);
}

int GamepadService::Pad2Up() {
	return _PAD(1, PADLup);
}

int GamepadService::Pad2Down() {
	return _PAD(1, PADLdown);
}

int GamepadService::Pad2Left() {
	return _PAD(1, PADLleft);
}

int GamepadService::Pad2Right() {
	return _PAD(1, PADLright);
}

int GamepadService::Pad2Triangle() {
	return _PAD(1, PADRup);
}

int GamepadService::Pad2Cross() {
	return _PAD(1, PADRdown);
}

int GamepadService::Pad2Square() {
	return _PAD(1, PADRleft);
}

int GamepadService::Pad2Circle() {
	return _PAD(1, PADRright);
}

int GamepadService::Pad2L1() {
	return _PAD(1, PADL1);
}

int GamepadService::Pad2L2() {
	return _PAD(1, PADL2);
}

int GamepadService::Pad2R1() {
	return _PAD(1, PADR1);
}

int GamepadService::Pad2R2() {
	return _PAD(1, PADR2);
}

int GamepadService::Pad2Start() {
	return _PAD(1, PADstart);
}

int GamepadService::Pad2Select() {
	return _PAD(1, PADselect);
}
