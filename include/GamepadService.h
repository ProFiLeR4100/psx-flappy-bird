#ifndef GAMEPAD_SERVICE_H
#define GAMEPAD_SERVICE_H

struct GamepadService {
	static int SysPad;
	static int SysPadT;

	static void initialize();

	static void padReset();

	static void padUpdate();

	static int padCheck(int pad);

	static int padCheckPressed(int pad);

	static int Pad1Up();

	static int Pad1Down();

	static int Pad1Left();

	static int Pad1Right();

	static int Pad1Triangle();

	static int Pad1Cross();

	static int Pad1Square();

	static int Pad1Circle();

	static int Pad1L1();

	static int Pad1L2();

	static int Pad1R1();

	static int Pad1R2();

	static int Pad1Start();

	static int Pad1Select();

	static int Pad2Up();

	static int Pad2Down();

	static int Pad2Left();

	static int Pad2Right();

	static int Pad2Triangle();

	static int Pad2Cross();

	static int Pad2Square();

	static int Pad2Circle();

	static int Pad2L1();

	static int Pad2L2();

	static int Pad2R1();

	static int Pad2R2();

	static int Pad2Start();

	static int Pad2Select();
};

#endif // GAMEPAD_SERVICE_H