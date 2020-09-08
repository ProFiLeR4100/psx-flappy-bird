#include <LIBMATH.H>
#include <STDIO.H>
#include <Sprite.h>
#include "PhysicsService.h"

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

bool PhysicsService::Intersects2D(Sprite *a, Sprite *b)  {
	if(PHYSICS_SERVICE_MODE) printf("=====================================\nCollision check started\n");
	// <editor-fold desc="Circles">
	if (COLLIDER_TYPE_CIRCLE == a->collider->type && COLLIDER_TYPE_CIRCLE == b->collider->type) {
		CircleCollider* aC = (CircleCollider*) a;
		CircleCollider* bC = (CircleCollider*) b;
		if(PHYSICS_SERVICE_MODE) printf("Checking circles collision\nDiff 1: %d\nDiff 2: %d", (int) (aC->radius - bC->radius), (int) (bC->radius - aC->radius));

		if(PHYSICS_SERVICE_MODE) printf("Collision check Ended\n=====================================\n");
		return aC->radius - bC->radius < 0 || bC->radius - aC->radius < 0;
	}
	// </editor-fold>

	// <editor-fold desc="Rectangle & Circle">
	if (COLLIDER_TYPE_RECT == a->collider->type && COLLIDER_TYPE_CIRCLE == b->collider->type
		|| COLLIDER_TYPE_CIRCLE == a->collider->type && COLLIDER_TYPE_RECT == b->collider->type) {
		Sprite *rectangle;
		Sprite* circle;

		if (COLLIDER_TYPE_RECT == a->collider->type) {
			rectangle = a;
			circle = b;
		} else {
			rectangle = b;
			circle = a;
		}

		CircleCollider* circleCollider = (CircleCollider*) circle->collider;
		float sqRadius = circleCollider->radius * circleCollider->radius;
		bool intersects = false;
		LINE_F2 line;

		for (int i = 0; i < 4; i++) {
			switch (i) {
				case 0: // TOP
					line.x0 = (short) rectangle->position.vx - rectangle->image.sprite.mx;
					line.x1 = (short) rectangle->position.vx + rectangle->image.sprite.w - rectangle->image.sprite.mx;
					line.y0 = (short) rectangle->position.vy - rectangle->image.sprite.my;
					line.y1 = (short) rectangle->position.vy - rectangle->image.sprite.my;
					intersects |= PhysicsService::sqPerpendicuralDistance(line, circle->position) - sqRadius < 0;
					break;
				case 1: // RIGHT
					line.x0 = (short) rectangle->position.vx + rectangle->image.sprite.w - rectangle->image.sprite.mx;
					line.x1 = (short) rectangle->position.vx + rectangle->image.sprite.w - rectangle->image.sprite.mx;
					line.y0 = (short) rectangle->position.vy - rectangle->image.sprite.my;
					line.y1 = (short) rectangle->position.vy + rectangle->image.sprite.h - rectangle->image.sprite.my;
					intersects |= PhysicsService::sqPerpendicuralDistance(line, circle->position) - sqRadius < 0;
					break;
				case 2: // BOTTOM
					line.x0 = (short) rectangle->position.vx - rectangle->image.sprite.mx;
					line.x1 = (short) rectangle->position.vx + rectangle->image.sprite.w - rectangle->image.sprite.mx;
					line.y0 = (short) rectangle->position.vy + rectangle->image.sprite.h - rectangle->image.sprite.my;
					line.y1 = (short) rectangle->position.vy + rectangle->image.sprite.h - rectangle->image.sprite.my;
					intersects |= PhysicsService::sqPerpendicuralDistance(line, circle->position) - sqRadius < 0;
					break;
				case 3: // LEFT
					line.x0 = (short) rectangle->position.vx - rectangle->image.sprite.mx;
					line.x1 = (short) rectangle->position.vx - rectangle->image.sprite.mx;
					line.y0 = (short) rectangle->position.vy - rectangle->image.sprite.my;
					line.y1 = (short) rectangle->position.vy + rectangle->image.sprite.h - rectangle->image.sprite.my;
					intersects |= PhysicsService::sqPerpendicuralDistance(line, circle->position) - sqRadius < 0;
					break;
			}


			if(PHYSICS_SERVICE_MODE) printf("-------------------------------------\nLine Position: %d, %d -> %d. %d\n",
											line.x0, line.y0,
											line.x1, line.y1);
//			if(PHYSICS_SERVICE_MODE) printf("-------------------------------------\nChecking rect/circle collision:\nDirection: %d\nDiff: %d\nLine Position: %d, %d -> %d. %d\nCircle Position: %d, %d\nCircle Radius^2: %d\n",
//					   i,
//					   (int) (PhysicsService::sqPerpendicuralDistance(line, circle->position) - sqRadius),
//					   line.x0, line.y0,
//					   line.x1, line.y1,
//					   (int) circle->position.vx,
//					   (int) circle->position.vy,
//					   (int) sqRadius);
		}

		if(PHYSICS_SERVICE_MODE) printf("Collision check Ended\n=====================================\n");
		return intersects;
	}
	// </editor-fold>

	if(PHYSICS_SERVICE_MODE) printf("No Collision condition check found\nCollision check Ended\n=====================================\n");
	return false;
}
