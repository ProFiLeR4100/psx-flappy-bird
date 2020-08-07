#include <DisplayService.h>
#include <LIBGS.H>

int DisplayService::SCREEN_WIDTH;
int DisplayService::SCREEN_HEIGHT;
Color DisplayService::systemBackgroundColor;
GsOT DisplayService::orderingTable[2];
GsOT_TAG DisplayService::minorOrderingTable[2][1 << OT_LENGTH];
short DisplayService::currentBuffer;
PACKET DisplayService::GPUOutputPacket[2][PACKETMAX];

void DisplayService::initialize() {
	setScreenMode(*(char *) 0xbfc7ff52 == 'E' ? SCREEN_MODE_PAL : SCREEN_MODE_NTSC);
	SetDispMask(1);
	ResetGraph(0);
	DisplayService::clearVRAM();
	GsInitGraph(SCREEN_WIDTH, SCREEN_HEIGHT, GsINTER | GsOFSGPU, 1, 0); //Set up interlation..
	GsDefDispBuff(0, 0, 0, SCREEN_HEIGHT);	//..and double buffering.
	systemBackgroundColor = ColorHelper::fromRGB(0, 0, 255);
	initializeOrderingTable();
}

void DisplayService::setScreenMode(int mode) {
	if (mode == SCREEN_MODE_PAL) { // SCEE string address
		// PAL MODE
		SCREEN_WIDTH = 320;
		SCREEN_HEIGHT = 256;
		if (DISPLAY_SERVICE_MODE) printf("Setting the PlayStation Video Mode to (PAL %dx%d)\n", SCREEN_WIDTH, SCREEN_HEIGHT);
		SetVideoMode(1);
		if (DISPLAY_SERVICE_MODE) printf("Video Mode is (%d)\n", (int) GetVideoMode());
	} else {
		// NTSC MODE
		SCREEN_WIDTH = 320;
		SCREEN_HEIGHT = 240;
		if (DISPLAY_SERVICE_MODE) printf("Setting the PlayStation Video Mode to (NTSC %dx%d)\n", SCREEN_WIDTH, SCREEN_HEIGHT);
		SetVideoMode(0);
		if (DISPLAY_SERVICE_MODE) printf("Video Mode is (%d)\n", (int) GetVideoMode());
	}
	GsInitGraph(SCREEN_WIDTH, SCREEN_HEIGHT, GsINTER | GsOFSGPU, 1, 0);
	GsDefDispBuff(0, 0, 0, SCREEN_HEIGHT);
}

void DisplayService::clearVRAM() {
	RECT rectTL;
	setRECT(&rectTL, 0, 0, 1024, 512);
	ClearImage2(&rectTL, 0, 0, 0);
	DrawSync(0);
}

void DisplayService::initializeOrderingTable() {
	GsClearOt(0, 0, &orderingTable[GsGetActiveBuff()]);

	// initialise the ordering tables
	orderingTable[0].length = OT_LENGTH;
	orderingTable[1].length = OT_LENGTH;
	orderingTable[0].org = minorOrderingTable[0];
	orderingTable[1].org = minorOrderingTable[1];

	GsClearOt(0, 0, &orderingTable[0]);
	GsClearOt(0, 0, &orderingTable[1]);
}

void DisplayService::setBackgroundColor(Color color) {
	systemBackgroundColor = color;
}

void DisplayService::display() {
	currentBuffer = GsGetActiveBuff();
	DrawSync(0);
	VSync(0);
	GsSwapDispBuff();
	GsSortClear(systemBackgroundColor.r, systemBackgroundColor.g, systemBackgroundColor.b, &orderingTable[currentBuffer]);
	GsDrawOt(&orderingTable[currentBuffer]);
}

void DisplayService::clearDisplay() {
	currentBuffer = GsGetActiveBuff();
	FntFlush(-1);
	GsSetWorkBase((PACKET*)GPUOutputPacket[currentBuffer]);
	GsClearOt(0, 0, &orderingTable[currentBuffer]);
}

void DisplayService::drawImage(Image image) {
	currentBuffer = GsGetActiveBuff();
	GsSortSprite(&image.sprite, &orderingTable[currentBuffer], 0);
}

Image DisplayService::createImage(unsigned char imageData[]) {

	// Initialize image
	Image image;
	GsGetTimInfo ((u_long *)(imageData+4),&image.tim_data);

	// Load the image into the frame buffer
	image.rect.x = image.tim_data.px;				// tim start X coord to put image data in frame buffer
	image.rect.y = image.tim_data.py;				// tim start Y coord to put image data in frame buffer
	image.rect.w = image.tim_data.pw;				// data width
	image.rect.h = image.tim_data.ph;				// data height
	LoadImage(&image.rect, image.tim_data.pixel);
	if (DISPLAY_SERVICE_MODE) printf("Rect info {x=%d, y=%d, w=%d, h=%d}\n", image.rect.x, image.rect.y, image.rect.w, image.rect.h);

	// Load the CLUT into the frame buffer
	image.crect.x = image.tim_data.cx;				// x pos to put CLUT in frame buffer
	image.crect.y = image.tim_data.cy;		   	// y pos to put CLUT in frame buffer
	image.crect.w = image.tim_data.cw;				// width of CLUT
	image.crect.h = image.tim_data.ch;				// height of CLUT
	LoadImage(&image.crect, image.tim_data.clut);
	if (DISPLAY_SERVICE_MODE) printf("CLUT info {x=%d, y=%d, w=%d, h=%d}\n", image.crect.x, image.crect.y, image.crect.w, image.crect.h);

	// Initialize sprite
	image.sprite.attribute = 0x1000000; 			// (0x1 = 8-bit, 0x2 = 16-bit)
	image.sprite.x = 0;						 	// draw at x coord
	image.sprite.y = 0;						  	// draw at y coord
	image.sprite.w = image.tim_data.pw * 2;		 // width of sprite
	image.sprite.h = image.tim_data.ph;			 // height of sprite
	if (DISPLAY_SERVICE_MODE) printf("Sprite mes {attribute = %d, x=%d, y=%d, w=%d, h=%d}\n", (int) image.sprite.attribute, image.sprite.x, image.sprite.y, image.sprite.w, image.sprite.h);

	image.sprite.tpage = GetTPage(
			1,   								// 0=4-bit, 1=8-bit, 2=16-bit
			1,   								// semitransparency rate
			image.tim_data.px, 						// framebuffer pixel x
			image.tim_data.py  						// framebuffer pixel y
	);
	if (DISPLAY_SERVICE_MODE) printf("Tpage info {tpage = %d}\n", image.sprite.tpage);

	image.sprite.r = 128;							// color red blend
	image.sprite.g = 128;							// color green blend
	image.sprite.b = 128;							// color blue blend
	image.sprite.u=(image.tim_data.px - 320) * 2;   // position within timfile for sprite
	image.sprite.v=image.tim_data.py;				// position within timfile for sprite
	image.sprite.cx = image.tim_data.cx;			// CLUT location x
	image.sprite.cy = image.tim_data.cy;			// CLUT location y
	image.sprite.mx = 0;							// rotation x coord
	image.sprite.my = 0;							// rotation y coord
	image.sprite.scalex = ONE;					  // scale x (ONE = 100%)
	image.sprite.scaley = ONE;					  // scale y (ONE = 100%)
	image.sprite.rotate = 0;						// rotation

	return image;
}


Image DisplayService::scaleImage(Image image, short scaleX, short scaleY) {
	image.sprite.scalex = (short)(ONE * scaleX);
	image.sprite.scaley = (short)(ONE * scaleY);
	return image;
}