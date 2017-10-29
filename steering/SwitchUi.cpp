#include "Game.h"
#include "UiManager.h"
#include "GameMessageManager.h"
#include "SwitchUI.h"

SwitchUiMessage::SwitchUiMessage() : GameMessage(SWITCH_UI_MESSAGE)
{

}

SwitchUiMessage::~SwitchUiMessage()
{

}

void SwitchUiMessage::process()
{
	UI_MANAGER->switchUI();
}