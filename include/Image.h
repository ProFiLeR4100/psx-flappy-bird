#include <LIBGPU.H>
#include <LIBGS.H>

#ifndef IMAGE_STRUCT
#define IMAGE_STRUCT

struct Image {
	RECT rect;
	RECT crect;
	GsIMAGE tim_data;
	GsSPRITE sprite;
};

#endif // IMAGE_STRUCT

