#include "VelocityMatching.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"

VelocityMatching::VelocityMatching(KinematicUnit* pMover, float radius, int unitIndex)
{
	mpThisUnit = pMover;
	mpFlockmates = UNIT_MANAGER->getUnitList();
	mRadius = radius;
	mUnitIndex = unitIndex;
}

Steering* VelocityMatching::getSteering()
{
	mLinear = 0;
	mAngular = 0;
	Vector2D direction;
	float distance;

	for (int i = 0; i < UNIT_MANAGER->getUnitList().size(); i++)
	{

		//Check if the target is close
		direction = UNIT_MANAGER->getKinematicUnit(i)->getPosition() - mpThisUnit->getPosition();
		distance = direction.getLength();
		
		if (distance > mRadius)
		{
			// Acceleration tries to get to the target velocity
			mLinear += UNIT_MANAGER->getKinematicUnit(i)->getVelocity() - mpThisUnit->getVelocity();
			mLinear /= mTimeToTarget;
		}

		
		
	}

	// Average by the number of units calculated 
	//if(count > 0)
	//	mLinear /= count;

	// Check if the acceleration is too fast
	if (mLinear.getLength() > mpThisUnit->getMaxAcceleration())
	{
		mLinear.normalize();
		mLinear *= mpThisUnit->getMaxAcceleration();
	}


	// Output the steering
	return this;
}

