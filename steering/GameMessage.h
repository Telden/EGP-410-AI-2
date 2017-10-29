#pragma once

#include "Trackable.h"

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	DRAW_TEXT_MESSAGE = 1,
	CREATE_DYNAMIC_ARRIVE_UNIT_MESSAGE = 3,
	CREATE_DYNAMIC_SEEK_MESSAGE = 4,
	DELETE_UNIT_MESSAGE = 5,
	CREATE_WANDER_SEEK_UNIT,
	CREATE_WANDER_FLEE_UNIT,
	UPDATE_MOUSE_UI_MESSAGE,
	UPDATE_UNIT_UI_MESSAGE,
	CHANGE_UNIT_VALUE_MESSAGE,
	SWITCH_UI_MESSAGE,
	CREATE_BOID_FLOCK_MESSAGE,
	END_GAME_MESSAGE  
};

class GameMessage: public Trackable
{
public:
	friend class GameMessageManager;

	GameMessage( MessageType type  );
	~GameMessage();

	double getSubmittedTime() const { return mSubmittedTime; };
	double getScheduledTime() const { return mScheduledTime; };

protected:
	MessageType mType;
	double mSubmittedTime;
	double mScheduledTime;

private:
	virtual void process() = 0; 
};

