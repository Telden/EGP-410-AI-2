#include "KinematicWanderSteering.h"
#include "DynamicSeekSteering.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "GraphicsSystem.h"
#include <time.h> 
#include <stdlib.h>

KinematicWanderSteering::KinematicWanderSteering(KinematicUnit *pMover)
:mpMover(pMover)
{
	mApplyDirectly = true;
	srand(time(NULL));
	mpDynamicSeek = NULL;
}

Steering* KinematicWanderSteering::getSteering()
{
	mAngular = 0; mLinear = 0;
	if (mFrameDelay == 0)
	{
		Vector2D target;
		target.setX(rand() % WIDTH);
		target.setY (rand() % HEIGHT);
		if (mpDynamicSeek != NULL)
			delete mpDynamicSeek;
		mpDynamicSeek = new DynamicSeekSteering(mpMover, target);
		
		mFrameDelay = mResetFrameDelay;

		
		
		
	}

	else
		mFrameDelay--;
	
	return mpDynamicSeek->getSteering();
	
	
	
	//mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity(); 
	//mAngular = mpMover->getOrientation() + ( genRandomBinomial() * MAX_WANDER_ROTATION );
	//return this;
}