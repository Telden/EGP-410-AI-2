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
	Sprite* mpEnemySprite;
	int seed;
public:
	UnitManager();
	~UnitManager();

	void addUnit(KinematicUnit* newUnit);
	void createDynamicArriveUnit();
	void createDynamicSeekUnit();
	void deleteUnit();
	void updateUnits(float time);
	void cleanup();

};
#endif 