#include <LIBGTE.H>
#include "Vector2F.h"
#include <LIBGPU.H>

#ifndef PHYSICS_SERVICE_H
#define PHYSICS_SERVICE_H

struct PhysicsService {
	static float fGravity;

	static void updatePosition(float* fAcceleration, float* fVelocity, float* fWeight, Vector2F* position, float fElapsedTime);

	static float sqEuclideanDistance(LINE_F2 line);

	static float sqPerpendicuralDistance(LINE_F2 line, Vector2F point);
};

#endif // PHYSICS_SERVICE_H