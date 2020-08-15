#include <LIBGTE.H>
#include "Vector2F.h"

#ifndef PHYSICS_SERVICE_H
#define PHYSICS_SERVICE_H

struct PhysicsService {
	static float fGravity;

	static void updatePosition(float* fAcceleration, float* fVelocity, float* fWeight, Vector2F* position, float fElapsedTime) {
		*fAcceleration += fGravity * fElapsedTime;

		if (*fAcceleration >= fGravity) {
			*fAcceleration = fGravity;
		}

		*fVelocity += *fAcceleration * fElapsedTime;

		position->vy += *fVelocity * fElapsedTime;
	}
};

#endif // PHYSICS_SERVICE_H