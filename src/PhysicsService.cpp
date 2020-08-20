#include "PhysicsService.h"
#include <LIBMATH.H>

float PhysicsService::fGravity = 100;

void PhysicsService::updatePosition(float *fAcceleration, float *fVelocity, float *fWeight, Vector2F *position, float fElapsedTime) {
	*fAcceleration += fGravity * fElapsedTime;

	if (*fAcceleration >= fGravity) {
		*fAcceleration = fGravity;
	}

	*fVelocity += *fAcceleration * fElapsedTime;

	position->vy += *fVelocity * fElapsedTime;
}

float PhysicsService::sqPerpendicuralDistance(LINE_F2 line, Vector2F point) {
	float dividend = fabs((line.y1 - line.y0) * point.vx
						  - (line.x1 - line.x0) * point.vy
						  + line.x1 * line.y0
						  - line.y1 * line.x0);
	float sqDividend = dividend * dividend;
	float sqDivider = PhysicsService::sqEuclideanDistance(line);

	return sqDividend / sqDivider;
}

float PhysicsService::sqEuclideanDistance(LINE_F2 line) {
	float y = (float) line.y1 - (float) line.y0;
	float x = (float) line.x1 - (float) line.x0;
	return y * y + x * x;
}
