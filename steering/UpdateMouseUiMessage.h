#pragma once
#include "GameMessage.h"

class UpdateMouseUiMessage : public GameMessage
{
private:
	float mMouseX, mMouseY;
	std::string mMousePos;
	std::string mCurrentSelection;
	
public:
	UpdateMouseUiMessage(float mouseX, float mouseY, std::string mousePos, std::string currentSelection);
	~UpdateMouseUiMessage();

	void process();
};