#pragma once
#include "Trackable.h"
#include "Steering.h"

struct BehaviorAndWeight : public Trackable
{
	Steering* mBehavior;
	float mWeight;

	BehaviorAndWeight() {};
	BehaviorAndWeight(Steering* behavior, float weight) { mBehavior = behavior; mWeight = weight; };
	~BehaviorAndWeight() {};
};