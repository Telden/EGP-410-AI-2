#pragma once
#include "Steering.h" //Don't know if I need this
#include <vector>

class BlendedSteering : public Steering
{
public:
	BlendedSteering();
	~BlendedSteering();
	Steering* getWeightedSteering();
	void addBehaviorandWeight(Steering* steeringPtr, float weight);

	//Struct contains one of the unit's behaviors and the weight assigned to that behavior
	struct BehaviorAndWeight : public Trackable
	{
		Steering* mpBehavior;
		float mWeight;

		BehaviorAndWeight(Steering* steering, float weight) { mpBehavior = steering; mWeight = weight; }
		~BehaviorAndWeight() {}
		
	};

private:
	std::vector<BehaviorAndWeight*> mpWeightedBehaviors;
	float mMaxAcceleration = 1.0f;
	float mMaxRotaion = 1.0f;

};
