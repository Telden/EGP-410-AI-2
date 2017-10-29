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
#include "Steering.h"
#include "BlendedSteering.h"
#include "BehaviorandWeight.h"
#include "CollisionAvoidance.h"
#include "Cohesion.h"
#include "Separation.h"
#include "Allignment.h"
#include "VelocityMatching.h"
#include "WallDetection.h"
#include "KinematicWanderSteering.h"
#include "DynamicWanderAndSeek.h"


// Message headers
#include "GameMessage.h"
#include "GameMessageManager.h"
#include "UpdateUnitUiMessage.h"

UnitManager::UnitManager()
{
	mpEnemySprite = SPRITE_MANAGER->getSprite(AI_ICON_SPRITE_ID);
	mpHorizontalWallSprite = SPRITE_MANAGER->getSprite(HORIZONTAL_WALL_ID);
	mpVerticalWallSprite = SPRITE_MANAGER->getSprite(VERTICAL_WALL_ID);
	srand(time(NULL));

	Vector2D wallpos;
	wallpos.setX(0); wallpos.setY(0);
	KinematicUnit* mpUpperWall = new KinematicUnit(mpHorizontalWallSprite, wallpos, 0, 0, 0, 0, 0);
	mpHorizontalWalls.push_back(mpUpperWall);

	wallpos.setX(0); wallpos.setY(668);
	KinematicUnit* mpLowerWall = new KinematicUnit(mpHorizontalWallSprite, wallpos, 0, 0, 0, 0, 0);
	mpHorizontalWalls.push_back(mpLowerWall);


	wallpos.setX(0); wallpos.setY(0);
	KinematicUnit* mpLeftWall = new KinematicUnit(mpVerticalWallSprite, wallpos, 0, 0, 0, 0, 0);
	mpVerticalWalls.push_back(mpLeftWall);

	wallpos.setX(924); wallpos.setY(0);
	KinematicUnit* mpRightWall = new KinematicUnit(mpVerticalWallSprite, wallpos, 0, 0, 0, 0, 0);
	mpVerticalWalls.push_back(mpRightWall);
}

UnitManager::~UnitManager()
{
	cleanup();
}

void UnitManager::addUnit(KinematicUnit* newUnit)
{
	mpUnits.push_back(newUnit);
}



/*delete a random unit from the screen other than the player*/
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

/*Update the units with new steering values, get their steering, and draw them*/
void UnitManager::updateUnits(float time)
{
	for (int i = 0; i < mpHorizontalWalls.size(); i++)
	{
		mpHorizontalWalls[i]->draw(GRAPHICS_SYSTEM->getBackBuffer());
	}
	for (int i = 0; i < mpVerticalWalls.size(); i++)
	{
		mpVerticalWalls[i]->draw(GRAPHICS_SYSTEM->getBackBuffer());
	}

	for (int i = 0; i < mpUnits.size(); i++)
	{
		if (mShouldUpdate)
		{
			mpUnits[i]->setRotationalVelocity(mAngularVelocity);
			mpUnits[i]->setMaxVelocity(mEnemyVelocity);
			mpUnits[i]->getSteering()->setRadius(mReactionRadius);
		}
		mpUnits[i]->update(time);
		mpUnits[i]->draw(GRAPHICS_SYSTEM->getBackBuffer());

	}

	

	if (mShouldUpdate)
		mShouldUpdate = false;

	
}

/*Destroys the objects in the Unit manager's vectors*/
void UnitManager::cleanup()
{

	for (int i = 0; i < mpUnits.size(); i++)
	{
		delete mpUnits[i];

	}

	for (int i = 0; i < mpHorizontalWalls.size(); i++)
	{
		delete mpHorizontalWalls[i];

	}

	for (int i = 0; i < mpVerticalWalls.size(); i++)
	{
		delete mpVerticalWalls[i];

	}
}

/* Updates values on the debug UI*/
void UnitManager::updateUI()
{
	GameMessage* pMessage = new UpdateUnitUiMessage(mReactionRadius, mAngularVelocity, mEnemyVelocity);
	MESSAGE_MANAGER->addMessage(pMessage, 0);
}

/*Recieves messages from the input manager and adjusts the selected unit attribute*/
void UnitManager::updateUnitValues(bool shouldIncrease, char currentSelection)
{
	if (shouldIncrease)
	{

		// increase selected value
		switch (currentSelection)
		{
		case 'V':
			// increase velocity
			printf("increaseing enemy velocity");
			mEnemyVelocity += mINCREASE_VALUE;
			mShouldUpdate = true;
			break;
		case 'R':
			//increase reaction radius
			printf("increaseing reaction radius");
			mReactionRadius += mINCREASE_VALUE;
			mShouldUpdate = true;
			break;
		case 'A':
			//Increase angular velocity
			printf("increaseing angular velocity");
			mAngularVelocity += mINCREASE_VALUE;
			mShouldUpdate = true;
			break;
		default:
			printf("Something went wrong in the increasing value switch of the change unit value message");
		}

	}
	else
	{
		// decrease selected value
		switch (currentSelection)
		{
		case 'V':
			// decrease velocity
			printf("decreasing enemy velocity");
			mEnemyVelocity -= mINCREASE_VALUE;
			mShouldUpdate = true;
			break;
		case 'R':
			// decrease reaction radius
			printf("increaseing reaction radius");
			mReactionRadius -= mINCREASE_VALUE;
			mShouldUpdate = true;
			break;
		case 'A':
			// decrease angular velocity
			printf("decreasing angular velocity");
			mAngularVelocity -= mINCREASE_VALUE;
			mShouldUpdate = true;
			break;
		default:
			printf("Something went wrong in the decreaseing value switch of the change unit value message");
		}
	}
}
std::vector<KinematicUnit*> UnitManager::getUnitList()
{
	return mpUnits;
}

std::vector<KinematicUnit*> UnitManager::getHoizontalWallList()
{
	return mpHorizontalWalls;
}
std::vector<KinematicUnit*> UnitManager::getVerticalWallList()
{
	return mpVerticalWalls;
}

KinematicUnit* UnitManager::getKinematicUnit(int index)
{
	return mpUnits[index];
}

void UnitManager::createBoidUnit(Vector2D mousePos)
{
	BehaviorAndWeight* pBAW;
	BlendedSteering* pBlendedSteering;
	Separation* pSeparation;
	Cohesion* pCohesion;
	Allignment* pAllignment;
	VelocityMatching* pVelocityMatching;
	CollisionAvoidance* pCollisionAvoidance;
	WallDetection* pWallDetection;
	KinematicWanderSteering* pWanderBehavior;
	int unitIndex;

	Vector2D mPos = mousePos;
	Vector2D vel(1.0f, 1.0f);
	KinematicUnit* pMover;


	//for (int i = 0; i < 5; i++)
	{
		pMover = new KinematicUnit(mpEnemySprite, mPos, 1, vel, mAngularVelocity, mEnemyVelocity, mMaxAcceleration);
		unitIndex = mpUnits.size();

		//Create the blending bahvior
		pBlendedSteering = new BlendedSteering(pMover); 

		//Set up the separation behavior
		pSeparation = new Separation(pMover, 50, DECAY_COEFFICIENT, unitIndex);
		pBAW = new BehaviorAndWeight(pSeparation, 90000);
		pBlendedSteering->addBehaviorAndWeight(pBAW);

		//Set up the cohesion behavior
		pCohesion = new Cohesion(pMover, mReactionRadius, DECAY_COEFFICIENT, unitIndex);
		pBAW = new BehaviorAndWeight(pCohesion, 10000);
		pBlendedSteering->addBehaviorAndWeight(pBAW);

		//Set up the Velocity matching behavior
		/*pVelocityMatching = new VelocityMatching(pMover, mReactionRadius, unitIndex);
		pBAW = new BehaviorAndWeight(pVelocityMatching, 2);
		pBlendedSteering->addBehaviorAndWeight(pBAW)*/;

		////Set up the Allignemnt behavior
		//pAllignment = new Allignment(pMover, mReactionRadius, SLOW_RADIUS);
		/*pBAW = new BehaviorAndWeight(pAllignment, 0.8);
		pBlendedSteering->addBehaviorAndWeight(pBAW);*/

		////Set up the wall detection behavior
		/*pWallDetection = new WallDetection(pMover);
		pBAW = new BehaviorAndWeight(pWallDetection, 2.0);
		pBlendedSteering->addBehaviorAndWeight(pBAW);*/

		////Set up the collision avoidance behavior
		//pCollisionAvoidance = new CollisionAvoidance(pMover, mReactionRadius, unitIndex);
		//pBAW = new BehaviorAndWeight(pCollisionAvoidance, 2.0);
		//pBlendedSteering->addBehaviorAndWeight(pBAW);

		//Set up the kinematic wander behavior
		/*pWanderBehavior = new KinematicWanderSteering(pMover);
		pBAW = new BehaviorAndWeight(pWanderBehavior, 1);
		pBlendedSteering->addBehaviorAndWeight(pBAW);*/

		//Add the blended behavior to the unit and add it to the unit manager vector
		pMover->setSteering(pBlendedSteering);
		addUnit(pMover);
	}
	

	pBAW = NULL;
	pBlendedSteering = NULL;
	pSeparation = NULL;
	pCohesion = NULL;
	pAllignment = NULL;
	pVelocityMatching = NULL;
	pCollisionAvoidance = NULL;
	pWallDetection = NULL;
	pWanderBehavior = NULL;
	pMover = NULL;
}






//void UnitManager::createDynamicArriveUnit()
//{
//	Vector2D mPos = mpUnits[0]->getPosition();
//	mPos.setX(mPos.getX() + 200);
//	Vector2D vel(0.0f, 0.0f);
//	KinematicUnit* mpAIUnit = new KinematicUnit(mpEnemySprite, mPos, 1, vel, mAngularVelocity, mEnemyVelocity, mMaxAcceleration);
//	mpAIUnit->dynamicArrive(&*mpUnits[0]);
//	addUnit(mpAIUnit);
//	mpAIUnit = NULL;
//}
//
//void UnitManager::createDynamicSeekUnit()
//{
//	Vector2D mPos = mpUnits[0]->getPosition();
//	mPos.setX(mPos.getX() - 100);
//	Vector2D vel(0.0f, 0.0f);
//	KinematicUnit* mpAIUnit = new KinematicUnit(mpEnemySprite, mPos, 1, vel, mAngularVelocity, mEnemyVelocity, mMaxAcceleration);
//	mpAIUnit->dynamicSeek(mpUnits[0]);
//	addUnit(mpAIUnit);
//	mpAIUnit = NULL;
//}
//
//void UnitManager::createDynamicWanderSeekUnit()
//{
//	Vector2D mPos = mpUnits[0]->getPosition();
//	mPos.setX(mPos.getX() - 200);
//	Vector2D vel(0.0f, 0.0f);
//	KinematicUnit* mpAIUnit = new KinematicUnit(mpEnemySprite, mPos, 1, vel, mAngularVelocity, mEnemyVelocity, mMaxAcceleration);
//	mpAIUnit->dynamicWanderandSeek(mpUnits[0], mReactionRadius);
//	//BlendedSteering* pBlendedSteering = mpAIUnit->blendedSteering(mpAIUnit);
//	//BehaviorAndWeight* pBAW = new BehaviorAndWeight(mpAIUnit->dynamicWanderandSeek(mpUnits[0], mReactionRadius), 0.05f);
//	//pBlendedSteering->addBehaviorAndWeight(pBAW);
//	//pBAW = new BehaviorAndWeight(mpAIUnit->collisionAvoidance(mpAIUnit, mReactionRadius), 2.0f);
//	//pBlendedSteering->addBehaviorAndWeight(pBAW);
//	 
//	addUnit(mpAIUnit);
//	mpAIUnit = NULL;
//	//pBlendedSteering = NULL;
//	//pBAW = NULL;
//}
//
//void UnitManager::createDynamicWanderFleeUnit()
//{
//	Vector2D mPos = mpUnits[0]->getPosition();
//	mPos.setX(mPos.getX() - 100);
//	Vector2D vel(0.0f, 0.0f);
//	KinematicUnit* mpAIUnit = new KinematicUnit(mpEnemySprite, mPos, 1, vel, mAngularVelocity, mEnemyVelocity, mMaxAcceleration);
//	mpAIUnit->dynamicWanderandFlee(mpUnits[0], mReactionRadius);
//	//BlendedSteering* pBlendedSteering = mpAIUnit->blendedSteering(mpAIUnit);
//	//BehaviorAndWeight* pBAW = new BehaviorAndWeight(mpAIUnit->dynamicWanderandFlee(mpUnits[0], mReactionRadius), 0.05f);
//	//pBlendedSteering->addBehaviorAndWeight(pBAW);
//	//pBAW = new BehaviorAndWeight(mpAIUnit->collisionAvoidance(mpAIUnit, mReactionRadius), 2.0f);
//	//pBlendedSteering->addBehaviorAndWeight(pBAW);
//	addUnit(mpAIUnit);
//	mpAIUnit = NULL;
//}