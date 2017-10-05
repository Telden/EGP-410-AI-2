#include "Game.h"
#include "GameMessageManager.h"
#include "EndGameMessage.h"

EndGameMessage::EndGameMessage() : GameMessage(END_GAME_MESSAGE)
{

}

EndGameMessage::~EndGameMessage()
{

}

void EndGameMessage::process()
{
	END_GAME;
}