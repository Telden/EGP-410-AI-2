#pragma once

#include "Steering.h"

class KinematicUnit;

class DynamicSeekSteering:public Steering
{
public:
	DynamicSeekSteering( KinematicUnit* pMover, Vector2D target, bool shouldFlee = false );
	~DynamicSeekSteering(){};

	//void setTarget( KinematicUnit* pTarget ){ mpTarget = pTarget; };

	virtual Steering* getSteering();

	private:
		Vector2D mTarget;
		KinematicUnit* mpMover;
		bool mShouldFlee;
};