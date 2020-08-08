#include "Line.h"

#ifndef BOX_H
#define BOX_H

struct Box {
	Line line[4];
	int type;
};

#endif // BOX_H