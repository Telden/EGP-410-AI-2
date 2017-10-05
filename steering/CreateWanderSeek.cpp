#include "Game.h"
#include "UnitManager.h"
#include "GameMessageManager.h"
#include "CreateWanderSeek.h"

CreateWanderSeek::CreateWanderSeek() : GameMessage(CREATE_WANDER_SEEK_UNIT)
{

}

CreateWanderSeek::~CreateWanderSeek()
{
	
}

void CreateWanderSeek::process()
{
	//Call unit Manager here
}