#include "Cohesion.h"
#include "Game.h"
#include "UnitManager.h"
#include "KinematicUnit.h"
#include "Vector2D.h"
#include <math.h>
//http://harry.me/blog/2011/02/17/neat-algorithms-flocking/
//https://processing.org/examples/flocking.html
Cohesion::Cohesion(KinematicUnit* pUnit, float radius, float decayCoefficient, int unitIndex)
{
	mpThisUnit = pUnit;
	mRadius = radius;
	mpFlockmates = UNIT_MANAGER->getUnitList();
	mUnitIndex = unitIndex;
	mDecayCoefficient = decayCoefficient;
}

Steering* Cohesion::getSteering()
{
	mAngular = 0; mLinear = 0;
	//std::cout << "cohesion" << std::endl;
	Vector2D direction;
	Vector2D averagePosition;
	float distance;
	std::vector <Vector2D> unitVectors;

	// look at all Units and get the positions of the ones within a certain radius
	for (int i = 1; i < UNIT_MANAGER->getUnitList().size(); i++)
	{
		
		distance = sqrt(pow(mpThisUnit->getPosition().getX() - UNIT_MANAGER->getKinematicUnit(i)->getPosition().getX(), 2.0f)
			+ pow(mpThisUnit->getPosition().getY() - UNIT_MANAGER->getKinematicUnit(i)->getPosition().getY(), 2.0f));
		if (distance < mRadius)
		{
			unitVectors.push_back(UNIT_MANAGER->getKinematicUnit(i)->getPosition());
		}
	}


	// calculate the average position
	for (unsigned int i = 0; i < unitVectors.size(); i++)
	{
		averagePosition += unitVectors[i];
	}
	if (unitVectors.size() > 0)
	{
		averagePosition /= unitVectors.size();

	 direction = averagePosition - mpThisUnit->getPosition();
	 distance = sqrt(pow(mpThisUnit->getPosition().getX() - averagePosition.getX(), 2.0f) + pow(mpThisUnit->getPosition().getY() - averagePosition.getY(), 2.0f));
	float strength = min((mDecayCoefficient) / ((distance * distance) +1), mpThisUnit->getMaxAcceleration());

		// add the acceleration
		direction.normalize();
		mLinear += direction * strength;
	}
	

	return this;

}

















//Steering* Cohesion::getSteering()
//{
//	mLinear = 0; mAngular = 0;
//	Vector2D direction;
//	float distance;
//	int count;
//
//	for (int i = 0; i < mpFlockmates.size(); i++)
//	{
//
//		//Check if the target is close
//		direction = mpFlockmates[i]->getPosition() - mpThisUnit->getPosition();
//		distance = direction.getLength();
//
//		if (distance > mRadius && distance > 0)
//		{
//			direction = mpFlockmates[i]->getPosition() - mpThisUnit->getPosition();
//			direction.normalize();
//			direction /= distance;
//			mLinear += direction;
//			count++;
//		}
//	}
//
//	//Average by how many were used
//	if (count > 0)
//	{
//		mLinear /= count;
//		
//		mLinear.normalize();
//		mLinear *= mpThisUnit->getMaxVelocity(); //This may need to be changed
//		mLinear -= mpThisUnit->getVelocity();
//		//mLinear.limit(maxforce); // <- need to cap the speed or accelleration
//	}
//	return this;
//
//	
//}