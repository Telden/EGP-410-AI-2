#include "Separation.h"
#include "KinematicUnit.h"
#include "Vector2D.h"
#include "Game.h"
#include "UnitManager.h"
Separation::Separation(KinematicUnit* pUnit, float radius, float nDecayCoefficient, int unitIndex)
{
	mpThisUnit = pUnit;
	mDecayCoefficient = nDecayCoefficient;
	setRadius(radius);
	mpPotentialTargets = UNIT_MANAGER->getUnitList();
	mUnitIndex = unitIndex;
}
 

Steering* Separation::getSteering()
{
	
	mAngular = 0; mLinear = 0;
	//std::cout << "cohesion" << std::endl;
	Vector2D direction;
	Vector2D averagePosition;
	float distance;
	std::vector <Vector2D> closePos;

	// look at all Units and get the positions of the ones within a certain radius
	for (int i = 1; i < UNIT_MANAGER->getUnitList().size(); i++)
	{


		distance = sqrt(pow(mpThisUnit->getPosition().getX() - UNIT_MANAGER->getKinematicUnit(i)->getPosition().getX(), 2.0f)
			+ pow(mpThisUnit->getPosition().getY() - UNIT_MANAGER->getKinematicUnit(i)->getPosition().getY(), 2.0f));
		if (distance < mRadius)
		{
			closePos.push_back(UNIT_MANAGER->getKinematicUnit(i)->getPosition());
		}
	}

	if (closePos.size() > 1)
	{
		//std::cout << "cohesion" << std::endl;
	}

	// calculate the average position
	for (unsigned int i = 0; i < closePos.size(); i++)
	{
		averagePosition += closePos[i];
	}
	if (closePos.size() > 0)
	{
		averagePosition /= closePos.size();

		// calculate the direction to the average position
		Vector2D direction = averagePosition - mpThisUnit->getPosition();
		// calculate the distance between the mover and the average position
		float distance = sqrt(pow(mpThisUnit->getPosition().getX() - averagePosition.getX(), 2.0f)
			+ pow(mpThisUnit->getPosition().getY() - averagePosition.getY(), 2.0f));
		// calculate the strength of the separation (also don't divide by zero)
		float strength = -min((0.1) / ((distance * distance) + 1), mpThisUnit->getMaxAcceleration());

		// add the acceleration
		direction.normalize();
		mLinear += direction * strength;
	}


	return this;
}