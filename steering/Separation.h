#pragma once
#include "Steering.h"
#include <vector>

class KinematicUnit;

class Separation : public Steering
{
public:
	Separation(KinematicUnit* pUnit, float radius, float nDecayCoefficient, int unitIndex);
	~Separation() {};
	virtual Steering* getSteering() ;

private:
	KinematicUnit* mpThisUnit;
	std::vector<KinematicUnit*> mpPotentialTargets;
	float mDecayCoefficient = 0;
	int mUnitIndex;
};