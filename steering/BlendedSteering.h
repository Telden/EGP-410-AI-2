#pragma once
#include "Steering.h"
#include "BehaviorandWeight.h"
#include <vector>

class KinematicUnit;
class Vector2D;

class BlendedSteering : public Steering
{
public:
	BlendedSteering(KinematicUnit* pUnit);
	~BlendedSteering();
	void checkMaxSpeed(Vector2D& a, float b);
	//void checkMaxRotation(float& angular, float maximum);
	void addBehaviorAndWeight(BehaviorAndWeight* nBAW);
	virtual Steering* getSteering();
private:
	std::vector<BehaviorAndWeight*> mpBehaviors;
	KinematicUnit* mpUnit;
	const float MAX_WANDER_ROTATION = 1.0f;
	
};