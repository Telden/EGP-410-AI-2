#pragma once
#include "GameMessage.h"

class CreateWanderSeek : public GameMessage
{
public:
	CreateWanderSeek();
	~CreateWanderSeek();
	void process();
};