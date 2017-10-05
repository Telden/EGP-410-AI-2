#include "Game.h"
#include "UnitManager.h"
#include "GameMessageManager.h"
#include "CreateWanderFlee.h"

CreateWanderFlee::CreateWanderFlee() : GameMessage(CREATE_WANDER_FLEE_UNIT)
{

}

CreateWanderFlee::~CreateWanderFlee()
{

}

void CreateWanderFlee::process()
{
	//Call Unit manager
}