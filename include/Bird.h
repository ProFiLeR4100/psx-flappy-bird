#include <LIBGTE.H>

#ifndef BIRD_H
#define BIRD_H
struct Bird: public GameObject {
public:
	Bird();

	void flap();
	virtual void draw();
	virtual void update(float fDeltaTime);
	virtual void updatePhysics(float fDeltaTime);

private:
	float fVelocity;
	float fAcceleration;
	float fWeight;
	Image birdFrames[3];
	float fFrame;
};

#endif // BIRD_H