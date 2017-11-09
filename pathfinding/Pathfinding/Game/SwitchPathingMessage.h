#pragma once
#include "GameMessage.h"


class SwitchPathingMessage : public GameMessage
{
public:
	SwitchPathingMessage(char input, GameApp* gameApp);
	~SwitchPathingMessage() {};

	void process();
private:
	char mInput;
	GameApp* mpGameApp;
};