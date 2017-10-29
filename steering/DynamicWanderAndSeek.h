#pragma once
#include "Steering.h"

class KinematicUnit;
class CollisionAvoidance;

class DynamicWanderAndSeek : public Steering
{
public:
	DynamicWanderAndSeek(KinematicUnit* pMover, KinematicUnit* pTarget, float radius, int UnitIndex, bool shouldflee);
	~DynamicWanderAndSeek() {  };

	void setTarget(KinematicUnit* pTarget) { mpTarget = pTarget; };
	void setRadius(float radius) { mRadius = radius; };
	virtual Steering* getSteering();

private:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
	const float MAX_WANDER_ROTATION = 0.5f;

	//Determines whether to be seeking or fleeing instead of wandering
	bool mShouldFlee;


	//Variable to determine whether the AI should be running away/seeking or wandering 
	bool mSeekFlee = true;


	//Dynamic Wander variables
	//Circle
	float mWanderOffset = 50;
	float mWanderRadius = 100;

	//Rate where the object changes its orientation
	int mWanderRate = 0;
	
	//Object's current orientation (creating this object once so it isn't a local variable not constnatly being created and destroyed
	float mWanderOriention;
	float mTargetOrientation;
	Vector2D mTarget;
	
	int mUnitIndex;
	//CollisionAvoidance* mpCollisionAvoidance;
};