#include <LIBGTE.H>
#include <LIBGPU.H>
#include "Vector2F.h"
#include "Sprite.h"
#include "Collider.h"
#include "CircleCollider.h"
#include "ColliderType.h"

#ifndef PHYSICS_SERVICE_H
#define PHYSICS_SERVICE_H

#define PHYSICS_SERVICE_MODE 1

struct PhysicsService {
	static float fGravity;

	static void updatePosition(float* fAcceleration, float* fVelocity, float* fWeight, Vector2F* position, float fElapsedTime);

	static float sqEuclideanDistance(LINE_F2 line);

	static float sqPerpendicuralDistance(LINE_F2 line, Vector2F point);

	static bool Intersects2D(Sprite *a, Sprite *b);
};

#endif // PHYSICS_SERVICE_H