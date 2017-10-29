#pragma once
#include "Steering.h"
#include <vector>

class KinematicUnit;

class Allignment : public Steering
{
public:
	Allignment(KinematicUnit* pMover, float radius, float slowRadius);
	Allignment() {};
	virtual Steering* getSteering();
	float mapToRange(float rotation);
private:
	KinematicUnit* mpThisUnit;
	std::vector<KinematicUnit*> mpFlockmates;
	float mSlowRadius;
	float mTimeToTarget = 0.1;
	const float MAX_ROTATION = 100;
};