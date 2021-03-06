#pragma once
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Trackable.h"
#include <allegro5/allegro.h>
class GameMessage;

class InputManager : public Trackable
{
private:

	bool mDKeyPressed = true;
	std::string mCurrentSelection = "V";
	char mInputSelection = 'V';
public:
	InputManager();
	~InputManager();
	void checkInput();
	bool init();
};
#endif // !INPUTMANAGER_H