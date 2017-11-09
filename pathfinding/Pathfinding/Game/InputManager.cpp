#include "InputManager.h"
#include "Defines.h"
#include <sstream>
#include <stdio.h>
#include "GameMessageManager.h"
#include "GameMessage.h"
#include "Game.h"
#include "Vector2D.h"
#include "GameApp.h"
#include "PathToMessage.h"
#include "SwitchPathingMessage.h"

// Messages



InputManager::InputManager()
{
	pGame = dynamic_cast<GameApp*>(gpGame);
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
		static Vector2D lastPos(0.0f, 0.0f);
		Vector2D pos(mouseState.x, mouseState.y);
		if (lastPos.getX() != pos.getX() || lastPos.getY() != pos.getY())
		{
			GameMessage* pMessage = new PathToMessage(lastPos, pos);
			pGame->getMessageManager()->addMessage(pMessage, 0);
			lastPos = pos;
		}
	}
	ALLEGRO_KEYBOARD_STATE keyState;
	al_get_keyboard_state(&keyState);

	//if escape key was down then exit the loop
	if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) 
	{
		gpGame->markForExit();
	}

	if (al_key_down(&keyState, ALLEGRO_KEY_D)) //Switch to Dijkstra
	{
		GameMessage* pMessage = new SwitchPathingMessage('D', pGame);
		pGame->getMessageManager()->addMessage(pMessage, 0);

	}
	if (al_key_down(&keyState, ALLEGRO_KEY_A)) //Switch to A*
	{
		GameMessage* pMessage = new SwitchPathingMessage('A', pGame);
		pGame->getMessageManager()->addMessage(pMessage, 0);

	}
	
	


}