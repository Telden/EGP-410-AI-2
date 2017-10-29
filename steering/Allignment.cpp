#include "Allignment.h"
#include "Game.h"
#include "KinematicUnit.h"
#include "UnitManager.h"
#include <math.h>
Allignment::Allignment(KinematicUnit* pMover, float radius, float slowRadius)
{
	mpThisUnit = pMover;
	mpFlockmates = UNIT_MANAGER->getUnitList();
	mRadius = radius;
	mSlowRadius = slowRadius;
}

Steering* Allignment::getSteering()
{
	//https://processing.org/examples/flocking.html
	mLinear = 0; mAngular = 0;
	Vector2D direction;
	float distance, rotationSize, targetRotation, angularAcceleration, count = 0;

	for (int i = 0; i <UNIT_MANAGER->getUnitList().size(); i++)
	{
		//Check if the target is close
		direction = UNIT_MANAGER->getKinematicUnit(i)->getPosition() - mpThisUnit->getPosition();
		distance = direction.getLength();

		if (distance > mRadius)
		{
			count++;
			mAngular = UNIT_MANAGER->getKinematicUnit(i)->getOrientation() - mpThisUnit->getOrientation();
			mAngular = mapToRange(mAngular);
			rotationSize = abs(mAngular);

			if (rotationSize < mRadius)
			{
				continue;
			}

			if (rotationSize > mSlowRadius)
			{
				targetRotation = MAX_ROTATION;
			}
			else
			{
				targetRotation = MAX_ROTATION * rotationSize / mSlowRadius;
			}
			mAngular += targetRotation - mpThisUnit->getOrientation(); // <- might need to change this
			mAngular /= mTimeToTarget;
			
			angularAcceleration = abs(mAngular);
			if (angularAcceleration > mpThisUnit->getMaxAcceleration()) // <- might need to change this
			{
				mAngular /= angularAcceleration;
				mAngular *= mpThisUnit->getMaxAcceleration();
			}
		}
	}
	if(count > 0)
		mAngular /= count;
	return this;
}

float Allignment::mapToRange(float angular)
{
	float orientation = angular;
	if (orientation < -PI)
	{
		while (orientation < -PI)
		{
			orientation += PI;
		}

	}
	else if (orientation > PI)
	{
		while (orientation > PI)
		{
			orientation -= PI;
		}
	}
	return orientation;
}