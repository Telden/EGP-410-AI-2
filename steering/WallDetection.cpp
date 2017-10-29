#include "Game.h"
#include "UnitManager.h"
#include "WallDetection.h"
#include "KinematicUnit.h"
#include <vector>

WallDetection::WallDetection(KinematicUnit* pMover)
{
	mpMover = pMover;
}

WallDetection::~WallDetection()
{

}

bool WallDetection::getDetection()
{
		if (mpMover->getPosition().getX() < 100
			|| mpMover->getPosition().getX() > 924)
		{
			return true;
		}


		if (mpMover->getPosition().getY() <  100
			|| mpMover->getPosition().getY() >  668)
		{
			return true;
		}
	return false;
}

