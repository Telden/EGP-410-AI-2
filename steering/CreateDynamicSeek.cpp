#include "Game.h"
#include "UnitManager.h"
#include "GameMessageManager.h"
#include "CreateDynamicSeek.h"

CreateDynamicSeek::CreateDynamicSeek():GameMessage(CREATE_DYNAMIC_SEEK_MESSAGE)
{
	
}

CreateDynamicSeek::~CreateDynamicSeek()
{

}

void CreateDynamicSeek::process()
{
	//UNIT_MANAGER->createDynamicSeekUnit();
}