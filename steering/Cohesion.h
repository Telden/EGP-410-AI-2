#pragma once
#include "Steering.h"
#include <vector>

class KinematicUnit;

const float DECAY_COEF_COH = 0.1f;

class Cohesion : public Steering
{
public:
	Cohesion(KinematicUnit* pUnit, float radius, float decayCoefficient, int unitIndex);
	~Cohesion() {};
	virtual Steering* getSteering();


private:
	KinematicUnit* mpThisUnit;
	std::vector<KinematicUnit*> mpFlockmates;
	float mDecayCoefficient = 0;
	int mUnitIndex;
	int unitNumber;
};