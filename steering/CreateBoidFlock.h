#pragma once
#include "GameMessage.h"
#include "Vector2D.h"

class CreateBoidFlock : public GameMessage
{
private:
	Vector2D mMousePos;

public:
	CreateBoidFlock(Vector2D mousePos);
	~CreateBoidFlock();
	void process();
};