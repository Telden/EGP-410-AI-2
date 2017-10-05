//Steering Behaviors
#include "DynamicSeekSteering.h"
#include "KinematicWanderSteering.h"
#include "DynamicArriveSteering.h"
#include "BlendedSteering.h"

//The unit
#include "KinematicUnit.h"

BlendedSteering::BlendedSteering()
{

}

BlendedSteering::~BlendedSteering()
{

}

//Purpose: To add a new behavior with its weight to be used within the weighted blending algorithm
void BlendedSteering::addBehaviorandWeight(Steering* steeringPtr, float weight)
{
	BehaviorAndWeight* pNewWeightedBehavior = new BehaviorAndWeight(steeringPtr, weight);
	mpWeightedBehaviors.push_back(pNewWeightedBehavior);
}

Steering* BlendedSteering::getWeightedSteering()
{
	Steering* pSteering = new Steering();
	//float pSteering;

	for (int i = 0; i < mpWeightedBehaviors.size(); i++)
	{
		//pSteering += mpWeightedBehaviors[i]->mWeight * mpWeightedBehaviors[i]->mpBehavior->getSteering()->getLinear();
	}
	return pSteering;
}