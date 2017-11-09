#include "GameApp.h"
#include "SwitchPathingMessage.h"
#include "GridPathfinder.h"

SwitchPathingMessage::SwitchPathingMessage(char input, GameApp* gameApp) :GameMessage(SWITCH_PATHING_MESSAGE)
{
	mpGameApp = gameApp;
	mInput = input;
}

void SwitchPathingMessage::process()
{
	mpGameApp->switchPath(mInput);
	mpGameApp->getPathfinder()->switchColor(mInput);
	mpGameApp = NULL;
}