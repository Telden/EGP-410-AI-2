#include "DynamicWanderAndSeek.h"
#include "KinematicUnit.h"
#include "CollisionAvoidance.h"
#include "Game.h"
#include "WallDetection.h"
#include <math.h>

DynamicWanderAndSeek::DynamicWanderAndSeek(KinematicUnit *pMover, KinematicUnit* pTarget, float radius, int UnitIndex, bool shouldFlee)
	:mpMover(pMover)
	, mpTarget(pTarget)
	, mShouldFlee(shouldFlee)
{
	mApplyDirectly = false;
	setRadius(radius);
	mUnitIndex = UnitIndex;
	//mpCollisionAvoidance = new CollisionAvoidance(pMover, radius);
}

Steering* DynamicWanderAndSeek::getSteering()
{
	WallDetection tmpDetection(mpMover);
	CollisionAvoidance tmpSteering(mpMover, mRadius, mUnitIndex);
	if (tmpDetection.getDetection())
	{
		//printf("Detected wall");
		mpMover->setVelocity(mpMover->getVelocity() * -1);
		mLinear *-1;
		mpMover->setNewOrientation();
		return this;
	}
	else if (tmpSteering.getSteering() != NULL)
	{
		//printf("Tooclose");
		return  tmpSteering.getSteering();

	}
	else
	{
		mpMover->setRotationalVelocity(0.0f);
		//Calculate the distance between the object posision and the player posision
		float distance = sqrt(pow((mpTarget->getPosition().getX() - mpMover->getPosition().getX()), 2.0)
			+ pow((mpTarget->getPosition().getY() - mpMover->getPosition().getY()), 2.0));

		//If the distance is less than the radius, than the player object is inside the AI object's circle
		if (distance < mRadius)
			mSeekFlee = true;

		//When the unit is running away, it has to be a set distance away before it feels safe to wander again. This is to stop any potential jittery behavior
		else if (mSeekFlee && distance > mRadius + 500)
		{
			mSeekFlee = false;
			mAngular = 0;
			mLinear = 0;
			mpMover->setRotationalVelocity(0.0f);
		}

		if (mSeekFlee)
		{
			//If the object does not feel safe, it will flee from the player
			if (mShouldFlee)
			{
				printf("Running Away");
				mLinear = mpMover->getPosition() - mpTarget->getPosition();
				mLinear.normalize();
				mLinear *= mpMover->getMaxVelocity();

				mpMover->setNewOrientation();
				mAngular = mpMover->getOrientation();

			}

			else
			{
				printf("Seeking");
				mLinear = mpTarget->getPosition() - mpMover->getPosition();
				mLinear.normalize();
				mLinear *= mpMover->getMaxVelocity();

				mpMover->setNewOrientation();
				mAngular = mpMover->getOrientation();
			}
		}


		//If the object feels safe, then it will begin to wander
		else if (!mSeekFlee && mWanderRate == 0)
		{
			mLinear = 0;
			mAngular = 0;


			printf("Wandering");

			//mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();   //This does not work
			//mAngular = mpMover->getOrientation() + (genRandomBinomial() * MAX_WANDER_ROTATION);

			mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity(); //this works
			mpMover->setOrientation(mpMover->getOrientation() + genRandomBinomial());

			mWanderRate = 15;

		}
		else
			mWanderRate--;
	}
	
	return this;
}
