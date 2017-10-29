#include "Game.h"
#include "GameMessageManager.h"
#include "ChangeUnitValue.h"
#include "UnitManager.h"

ChangeUnitValue::ChangeUnitValue(bool shouldIncrease, char currentSelection) : GameMessage(CHANGE_UNIT_VALUE_MESSAGE)
{
	mShouldIncrease = shouldIncrease;
	mCurrentSelection = currentSelection;
}

ChangeUnitValue::~ChangeUnitValue()
{

}

void ChangeUnitValue::process()
{
	UNIT_MANAGER->updateUnitValues(mShouldIncrease, mCurrentSelection);
}