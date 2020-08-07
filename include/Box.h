#include "Line.h"

#ifndef BOX_STRUCT
#define BOX_STRUCT

class Box {
public:
	Line line[4];
	int type;
};

#endif // BOX_STRUCT