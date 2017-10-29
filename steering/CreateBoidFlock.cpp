#include "Game.h"
#include "GameMessageManager.h"
#include "CreateBoidFlock.h"
#include "UnitManager.h"

CreateBoidFlock::CreateBoidFlock(Vector2D mousePos) : GameMessage(CREATE_BOID_FLOCK_MESSAGE)
{
	mMousePos = mousePos;
}

CreateBoidFlock::~CreateBoidFlock()
{

}

void CreateBoidFlock::process()
{
	UNIT_MANAGER->createBoidUnit(mMousePos);
}