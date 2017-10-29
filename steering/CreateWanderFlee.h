#pragma once
#include "GameMessage.h"

class CreateWanderFlee : public GameMessage
{
public:
	CreateWanderFlee();
	~CreateWanderFlee();
	void process();
};