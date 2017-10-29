#pragma once
#include "Steering.h"
#include "DynamicSeekSteering.h"

class KinematicUnit;

class WallDetection : public Steering
{
public:
	WallDetection(KinematicUnit* pMover);
	~WallDetection();

	bool getDetection();
private:
	KinematicUnit* mpMover;
};