#pragma once
#include "Steering.h"
#include <vector>

class KinematicUnit;
class VelocityMatching : public Steering
{
public:
	VelocityMatching(KinematicUnit* pMover, float radius, int unitIndex);
	~VelocityMatching() {};
	virtual Steering* getSteering();

private:
	KinematicUnit* mpThisUnit;
	std::vector<KinematicUnit*> mpFlockmates;
	//std::vector<KinematicUnit*> mpPotentialTargets;
	float mTimeToTarget = 0.1;
	int mUnitIndex;
};