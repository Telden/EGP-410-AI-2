#include "InputManager.h"
#include "Defines.h"
#include <sstream>
#include <stdio.h>
#include "GameMessageManager.h"
#include "GameMessage.h"
#include "Game.h"

// Messages
#include "PlayerMoveToMessage.h"
#include "UpdateMouseUiMessage.h"
#include "CreateDynamicArrive.h"
#include "CreateDynamicSeek.h"
#include "CreateWanderFlee.h"
#include "CreateWanderSeek.h"
#include "DeleteUnitMessage.h"
#include "EndGameMessage.h"
#include "ChangeUnitValue.h"
#include "SwitchUI.h"
#include "CreateBoidFlock.h"


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
	Vector2D pos(mouseState.x, mouseState.y);
	if (al_mouse_button_down(&mouseState, 1))//left mouse click
	{
		
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
		//get mouse state

		al_get_mouse_state(&mouseState);

		//create mouse text
		std::stringstream mousePos;
		mousePos << mouseState.x << ":" << mouseState.y;
		GameMessage* pMessage = new UpdateMouseUiMessage(mouseState.x, mouseState.y, mousePos.str(), mCurrentSelection);
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
		
		//Create a dynamic wander and seek unit
		else if (al_key_down(&keyState, ALLEGRO_KEY_S))
		{

			pMessage = new CreateWanderSeek();
			MESSAGE_MANAGER->addMessage(pMessage, 0);

		}

		//Create a dynamic wander and flee unit
		else if (al_key_down(&keyState, ALLEGRO_KEY_F))
		{
				pMessage = new CreateWanderFlee();
				MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		//Send a message to the unit manager to delete a random unit other than the player unit
		else if (al_key_down(&keyState, ALLEGRO_KEY_D))
		{
			if (!mDKeyPressed)
			{
				pMessage = new DeleteUnitMessage();
				MESSAGE_MANAGER->addMessage(pMessage, 0);
				mDKeyPressed = true;
			}
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_I))
		{
			printf("I key pressed");
			if (!mDKeyPressed)
			{
				pMessage = new CreateBoidFlock(pos);
				MESSAGE_MANAGER->addMessage(pMessage, 0);
				mDKeyPressed = true;
			}
		}
		
		// Dubug key inputs
		else if (al_key_down(&keyState, ALLEGRO_KEY_U))
		{
			printf("U Key pressed");
			if (!mDKeyPressed)
			{
				pMessage = new SwitchUiMessage();
				MESSAGE_MANAGER->addMessage(pMessage, 0);
				mDKeyPressed = true;
			}
		}

		else if (al_key_down(&keyState, ALLEGRO_KEY_V))
		{
			mCurrentSelection = "V";
			mInputSelection = 'V';
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_R))
		{
			mCurrentSelection = "R";
			mInputSelection = 'R';
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_A))
		{
			mCurrentSelection = "A";
			mInputSelection = 'A';
		}

		else if (al_key_down(&keyState, ALLEGRO_KEY_EQUALS))
		{
			pMessage = new ChangeUnitValue(true, mInputSelection);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		
		}

		else if ((al_key_down(&keyState, ALLEGRO_KEY_MINUS )))
		{
			// decrease selected value
			pMessage = new ChangeUnitValue(false, mInputSelection);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}

		if (!al_key_down(&keyState, ALLEGRO_KEY_D) || !al_key_down(&keyState, ALLEGRO_KEY_I))
		{
			mDKeyPressed = false;
		}














		//Assignment 1 creation code

		/*else if (al_key_down(&keyState, ALLEGRO_KEY_A))
		{
		if (!mDKeyPressed)
		{
		pMessage = new CreateDynamicArrive();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
		mDKeyPressed = true;
		}
		}*/

		/*else if (al_key_down(&keyState, ALLEGRO_KEY_S))
		{

			pMessage = new CreateDynamicSeek();
			MESSAGE_MANAGER->addMessage(pMessage, 0);

		}*/

		

		
	}