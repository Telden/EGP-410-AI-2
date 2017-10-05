#include"Game.h"
#include "UnitManager.h"
#include "GameMessageManager.h"
#include "CreateDynamicArrive.h"

CreateDynamicArrive::CreateDynamicArrive() : GameMessage(CREATE_DYNAMIC_ARRIVE_UNIT_MESSAGE)
{
	
}

CreateDynamicArrive::~CreateDynamicArrive()
{

}

void CreateDynamicArrive::process()
{
	UNIT_MANAGER->createDynamicArriveUnit();
}