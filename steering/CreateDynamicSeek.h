#pragma once

#include  "GameMessage.h"


class CreateDynamicSeek : public GameMessage
{
public:
	CreateDynamicSeek();
	~CreateDynamicSeek();
	void process();
};