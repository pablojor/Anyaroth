#pragma once
#include "GameState.h"

class CreditsState : public GameState
{
private:
	bool _goodFinal = true;
public:
	CreditsState(Game* game, bool goodFinal = true);
	~CreditsState();

	virtual void start();
};