#ifndef PHYSICS_H
#define PHYSICS_H

#include <LIBGTE.H>

class Physics {
public:
	static const float fGravity = 100.0f;

	static void updatePosition(float* fAcceleration, float* fVelocity, float* fWeight, DVECTOR* position, float fElapsedTime) {
		*fAcceleration += fGravity * fElapsedTime;

		if (*fAcceleration >= fGravity) {
			*fAcceleration = fGravity;
		}

		*fVelocity += *fAcceleration * fElapsedTime;

		position->vy += (short)(*fVelocity * fElapsedTime);
	}
};

#endif // PHYSICS_H