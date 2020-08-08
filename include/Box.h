#include "Line.h"

#ifndef BOX_STRUCT
#define BOX_STRUCT

struct Box {
	Line line[4];
	int type;
};

#endif // BOX_STRUCT