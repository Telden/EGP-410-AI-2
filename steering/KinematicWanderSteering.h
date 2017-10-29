#pragma once

#include "Steering.h"
#include "Vector2D.h"

class KinematicUnit;
class DynamicSeekSteering;

const float MAX_WANDER_ROTATION = 1.0f;

class KinematicWanderSteering:public Steering
{
public:
	KinematicWanderSteering( KinematicUnit* pMover );
	~KinematicWanderSteering(){};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
	DynamicSeekSteering* mpDynamicSeek;
	int mFrameDelay = 0;
	int mResetFrameDelay = 60;
	const int WIDTH = 1024;
	const int HEIGHT = 768;

	Vector2D target;
};