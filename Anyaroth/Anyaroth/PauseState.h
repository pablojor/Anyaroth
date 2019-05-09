#pragma once
#include "GameState.h"
#include "PauseStateHUD.h"
class PauseState : public GameState
{
public:
	PauseState(Game* g);
	~PauseState() {}

	virtual void start();
};