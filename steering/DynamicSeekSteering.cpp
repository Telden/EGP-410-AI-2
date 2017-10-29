#include "DynamicSeekSteering.h"
#include "KinematicUnit.h"

DynamicSeekSteering::DynamicSeekSteering(KinematicUnit *pMover, Vector2D target, bool shouldFlee)
:mpMover(pMover)
,mTarget(target)
,mShouldFlee(shouldFlee)
{
	mApplyDirectly = false;
}

Steering* DynamicSeekSteering::getSteering()
{
	if( !mShouldFlee )
	{
		mLinear = mTarget - mpMover->getPosition();
	}
	else
	{
		mLinear = mpMover->getPosition() - mTarget;
	}

	mLinear.normalize();
	mLinear *= mpMover->getMaxAcceleration();
	mAngular = 0;
	return this;
}