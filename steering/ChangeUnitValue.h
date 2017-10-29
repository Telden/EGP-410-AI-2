#pragma once
#include "GameMessage.h"

class ChangeUnitValue : public GameMessage
{
private:
	bool mShouldIncrease;
	char mCurrentSelection;
public:
	ChangeUnitValue(bool shouldIncrease, char currentSelection);
	~ChangeUnitValue();

	void process();
};