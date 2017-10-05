#include "InputManager.h"
#include "Defines.h"
#include <sstream>
#include <stdio.h>
#include "GameMessageManager.h"
#include "GameMessage.h"
#include "PlayerMoveToMessage.h"
#include "DrawTextMessage.h"
#include "CreateDynamicArrive.h"
#include "CreateDynamicSeek.h"
#include "DeleteUnitMessage.h"
#include "EndGameMessage.h"
#include "Game.h"

InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

bool InputManager::init()
{
	if (!al_install_keyboard())
	{
		printf("Keyboard not installed!\n");
		return false;
	}

	if (!al_install_mouse())
	{
		printf("Mouse not installed!\n");
		return false;
	}

	return true;
}


void InputManager::checkInput()
{
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);
	if (al_mouse_button_down(&mouseState, 1))//left mouse click
	{
		Vector2D pos(mouseState.x, mouseState.y);
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
		//get mouse state

		al_get_mouse_state(&mouseState);

		//create mouse text
		std::stringstream mousePos;
		mousePos << mouseState.x << ":" << mouseState.y;
		GameMessage* pMessage = new DrawtextMessage(255, 255, 255, mouseState.x, mouseState.y, mousePos.str());
		MESSAGE_MANAGER->addMessage(pMessage, 0);

		//get current keyboard state
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);

		//if escape key was down then exit the loop
		if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
		{
			GameMessage* pMessage = new EndGameMessage();
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_A))
		{
			if (!mDKeyPressed)
			{
				pMessage = new CreateDynamicArrive();
				MESSAGE_MANAGER->addMessage(pMessage, 0);
				mDKeyPressed = true;
			}
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_D))
		{
			pMessage = new DeleteUnitMessage();
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_S))
		{
			pMessage = new CreateDynamicSeek();
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}

		if (!al_key_down(&keyState, ALLEGRO_KEY_D))
		{
			mDKeyPressed = false;
		}
	}