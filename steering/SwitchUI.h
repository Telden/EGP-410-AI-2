#pragma once
#include "GameMessage.h"

class SwitchUiMessage : public GameMessage
{
public:
	SwitchUiMessage();
	~SwitchUiMessage();
	
	void process();
};