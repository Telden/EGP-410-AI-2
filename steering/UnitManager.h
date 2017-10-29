#pragma once
#ifndef UNITMANAGER_H
#define UNITMANAGER_H

#include "Trackable.h"
#include <vector>
class Vector2D;


class Sprite;
class KinematicUnit;

class UnitManager : public Trackable
{
private:
	std::vector<KinematicUnit*> mpUnits;
	std::vector<KinematicUnit*> mpVerticalWalls;
	std::vector<KinematicUnit*> mpHorizontalWalls;
	Sprite* mpEnemySprite;
	Sprite* mpVerticalWallSprite;
	Sprite* mpHorizontalWallSprite;
	int seed;
	float mReactionRadius = 100.0f;
	float mAngularVelocity = 0.0f;
	float mEnemyVelocity = 180.0f;
	float mMaxAcceleration = 100.0f;
	bool mShouldUpdate = false;
	const int mINCREASE_VALUE = 1;

	const int DECAY_COEFFICIENT = 0.1;
	const int SLOW_RADIUS = 50;
	int separationRadius = 50;


	

public:
	UnitManager();
	~UnitManager();

	void addUnit(KinematicUnit* newUnit);
	void createDynamicArriveUnit();
	void createDynamicSeekUnit();
	void createDynamicWanderSeekUnit();
	void createDynamicWanderFleeUnit();

	void createBoidUnit(Vector2D mousePos);
	void deleteUnit();
	void updateUnits(float time);
	void cleanup();
	void updateUnitValues(bool shouldIncrease, char currentSelection);
	std::vector<KinematicUnit*> getUnitList();
	std::vector<KinematicUnit*> getHoizontalWallList();
	std::vector<KinematicUnit*> getVerticalWallList();
	void updateUI();
	KinematicUnit* getKinematicUnit(int index);


	
};
#endif 