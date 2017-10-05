#include <time.h>  
#include <stdlib.h> 
#include "UnitManager.h"
#include "Game.h"
#include "Vector2D.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "KinematicUnit.h"
#include "GraphicsSystem.h"
#include "GameMessageManager.h"
#include "GameMessage.h"
#include "EndGameMessage.h"

UnitManager::UnitManager()
{
	mpEnemySprite = SPRITE_MANAGER->getSprite(AI_ICON_SPRITE_ID);
	srand(time(NULL));
}

UnitManager::~UnitManager()
{
	cleanup();
}

void UnitManager::addUnit(KinematicUnit* newUnit)
{
	mpUnits.push_back(newUnit);
}

void UnitManager::createDynamicArriveUnit()
{
	Vector2D mPos = mpUnits[0]->getPosition();
	mPos.setX(mPos.getX() + 200);
	Vector2D vel(0.0f, 0.0f);
	KinematicUnit* mpAIUnit = new KinematicUnit(mpEnemySprite, mPos, 1, vel, 0.0f, 180.0f, 100.0f);
	mpAIUnit->dynamicArrive(&*mpUnits[0]);
	addUnit(mpAIUnit);
	mpAIUnit = NULL;
}

void UnitManager::createDynamicSeekUnit()
{
	Vector2D mPos = mpUnits[0]->getPosition();
	mPos.setX(mPos.getX() - 100);
	Vector2D vel(0.0f, 0.0f);
	KinematicUnit* mpAIUnit = new KinematicUnit(mpEnemySprite, mPos, 1, vel, 0.0f, 180.0f, 100.0f);
	mpAIUnit->dynamicSeek(mpUnits[0]);
	addUnit(mpAIUnit);
	mpAIUnit = NULL;
}

void UnitManager::deleteUnit()
{
	if (mpUnits.size() != 1)
	{
		seed = rand() % (mpUnits.size() - 1) + 1;
		KinematicUnit* tmp = mpUnits[seed];
		delete tmp;
		tmp = NULL;
		mpUnits.erase(mpUnits.begin() + seed);
	}
	
	if (mpUnits.size() == 1)
	{
		GameMessage* pMessage = new EndGameMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
		

	

}

void UnitManager::updateUnits(float time)
{
	for (int i = 0; i < mpUnits.size(); i++)
	{
		mpUnits[i]->update(time);
		mpUnits[i]->draw(GRAPHICS_SYSTEM->getBackBuffer());
	}
}

void UnitManager::cleanup()
{

	for (int i = 0; i < mpUnits.size(); i++)
	{
		delete mpUnits[i];

	}
}