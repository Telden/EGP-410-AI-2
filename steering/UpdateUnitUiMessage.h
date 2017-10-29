#pragma once
#include "GameMessage.h"

class UpdateUnitUiMessage : public GameMessage
{
private:
	float mReationRadius, mAngularVelocity, mEnemyVelocity;

public:
	UpdateUnitUiMessage(float reactionRadius, float angularVelocity, float enemyVelocity);
	~UpdateUnitUiMessage();

	void process();

};