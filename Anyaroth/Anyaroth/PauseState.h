#pragma once
#include "GameState.h"
#include "PauseStateHUD.h"
class PauseState : public GameState
{
private:
	PauseStateHUD* _pauseHUD;

public:
	PauseState(Game* g);
	~PauseState() {}
};