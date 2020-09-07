#include "ColliderType.h"

#ifndef COLLIDER_H
#define COLLIDER_H

class Collider {
public:
	ColliderType type;
	Collider *colliderListPtr[];
};

#endif