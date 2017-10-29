#pragma once

#include "Steering.h"
#include <vector>

class KinematicUnit;
class Vector2D;

class CollisionAvoidance : public Steering
{
public:
	CollisionAvoidance(KinematicUnit* pUnit, float radius, int UnitIndex);
	~CollisionAvoidance();

	Steering* getSteering();

private:
	KinematicUnit* mpUnit;
	std::vector<KinematicUnit*> mpTargets; //List of potential targets
	float dot(Vector2D& a, Vector2D& b);
	int mUnitIndex; // Used so it doesn't check itself

	
};