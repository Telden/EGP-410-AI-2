#include "Game.h"
#include "GameMessageManager.h"
#include "UpdateMouseUiMessage.h"
#include "UiManager.h"

UpdateMouseUiMessage::UpdateMouseUiMessage(float mouseX, float mouseY, std::string mousePos, std::string currentSelection) : GameMessage(UPDATE_MOUSE_UI_MESSAGE)
{
	mMouseX = mouseX; mMouseY = mouseY;
	mMousePos = mousePos;
	mCurrentSelection = currentSelection;
}

UpdateMouseUiMessage::~UpdateMouseUiMessage()
{

}

void UpdateMouseUiMessage::process()
{
	UI_MANAGER->updateMouseUiInformation(mMouseX, mMouseY, mMousePos, mCurrentSelection);
}