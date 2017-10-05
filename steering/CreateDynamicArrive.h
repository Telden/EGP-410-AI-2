#pragma once
#include "GameMessage.h"


class CreateDynamicArrive : public GameMessage
{
public: 
	CreateDynamicArrive();
	~CreateDynamicArrive();
	void process();
};