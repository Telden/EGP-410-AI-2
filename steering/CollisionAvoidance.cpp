#include "Game.h"
#include "UnitManager.h"
#include "CollisionAvoidance.h"
#include "KinematicUnit.h"
#include "Vector2D.h"
CollisionAvoidance::CollisionAvoidance(KinematicUnit* pUnit, float radius, int UnitIndex)
{
	mpUnit = pUnit;
	mpTargets = UNIT_MANAGER->getUnitList();
	setRadius(radius);
	mUnitIndex = UnitIndex;
}

CollisionAvoidance::~CollisionAvoidance()
{

}

Steering* CollisionAvoidance::getSteering()
{
	
	//Set up the first collision time
	float shortestTime = 9999;

	//Variables to save from the for loop
	KinematicUnit* closestTarget = NULL;
	float closestMinSeperation, closestDistance ;
	Vector2D closestRelativePosision, closestRelativeVel;

	//Testing for loop variables
	float relativeSpeed, timeToCollision, distance, minSeperation;
	Vector2D relativePosision, relativeVel;

	mAngular = 0; mLinear = 0;
	int count = UNIT_MANAGER->getUnitList().size();
	
	for (int i = 0; i < count; i++) // i = 1 so that the player is not considered
	{
		// Check if the unit being checked against is the same as the unit checking for avoidance
		
		if (i == mUnitIndex) //If the iterator index equals the index of the unit calling this function skip it
			continue;
		
		//Calculate time to collision
		 relativePosision = UNIT_MANAGER->getKinematicUnit(i)->getPosition() - mpUnit->getPosition();
		 relativeVel = UNIT_MANAGER->getKinematicUnit(i)->getVelocity() - mpUnit->getVelocity();
		 relativeSpeed = relativeVel.getLength();        
		 if (relativeSpeed == 0) //relativeVel.getLengthSquared();
			 relativeSpeed = 1;
			 timeToCollision = (dot(relativePosision, relativeVel)) / (relativeSpeed * relativeSpeed);

		 //Check if there will be a collision
		 distance = relativePosision.getLength(); //getLengthSquared();
		 minSeperation = distance - relativeSpeed*timeToCollision;
		if (minSeperation > 2 * mRadius)
			continue;

		//Check if it is the shortest collision
		if (timeToCollision > 0 && timeToCollision < shortestTime)
		{
			//Store data
			shortestTime = timeToCollision;
			closestTarget = UNIT_MANAGER->getKinematicUnit(i);
			closestMinSeperation = minSeperation;
			closestDistance = distance;
			closestRelativePosision = relativePosision;
			closestRelativeVel = relativeVel;
		}
	}
	// If there are no other valid targets
	if (closestTarget == NULL)
	{
		return this;
	}
		

	//If the unit is going to hit exactly or is already colliding
	if (closestMinSeperation <= 0 || closestDistance < 2 * mRadius)
	{
		relativePosision = closestTarget->getPosition() + mpUnit->getPosition();
	}

	//Caluclate future relative posision
	else
	{
		relativePosision = closestRelativePosision + closestRelativeVel * shortestTime;
	}

	printf("too close");
	//Avoid the target
	relativePosision.normalize();
	mLinear = (relativePosision * mpUnit->getMaxAcceleration()); //* -1;

	return this;
}

float CollisionAvoidance::dot(Vector2D& a, Vector2D& b)
{
	float product;
	product = a.getX() * b.getX() + a.getY() * b.getY();
	return product;
}



