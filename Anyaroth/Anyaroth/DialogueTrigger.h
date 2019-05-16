#pragma once
#include "Trigger.h"
#include "PlayStateHUD.h"

class DialogueTrigger :
	public Trigger
{
private:
	Player* _player = nullptr;
public:
	DialogueTrigger(Game* game, string data, Player* player, int xPos = 0, int yPos = 0);
	virtual ~DialogueTrigger();

	PlayStateHUD* getPlayHUD();
};

