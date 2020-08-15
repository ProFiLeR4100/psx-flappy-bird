#include <LIBGS.H>
#include <LIBGPU.H>
#include <LIBETC.H>
#include <STDIO.H>
#include <ColorHelper.h>
#include "Image.h"

#ifndef DISPLAY_SERVICE_H
#define DISPLAY_SERVICE_H

#define SCREEN_MODE_PAL 0
#define SCREEN_MODE_NTSC 1
#define DISPLAY_SERVICE_MODE 0
#define OT_LENGTH 1
#define PACKETMAX 500

struct DisplayService {
	static Color systemBackgroundColor;
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	static GsOT orderingTable[2];
	static GsOT_TAG minorOrderingTable[2][1 << OT_LENGTH];
	static short currentBuffer;
	static PACKET GPUOutputPacket[2][PACKETMAX];

	static void initialize();

	static void clearVRAM();

	static void initializeOrderingTable();

	static void setScreenMode(int mode);

	static void setBackgroundColor(Color color);

	static void display();

	static void clearDisplay();

	static void drawImage(Image image);

	static Image createImage(unsigned char imageData[]);

	static Image scaleImage(Image image, short scaleX, short scaleY);
};
#endif // DISPLAY_SERVICE_H