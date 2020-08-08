#include <LIBGPU.H>
#include <LIBGS.H>

#ifndef IMAGE_H
#define IMAGE_H

struct Image {
	RECT rect;
	RECT crect;
	GsIMAGE tim_data;
	GsSPRITE sprite;
};

#endif // IMAGE_H

