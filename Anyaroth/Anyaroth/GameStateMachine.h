#pragma once
#include <stack>
#include "GameState.h"

class GameStateMachine
{
private:
	stack <GameState*> _states;

public:
	GameStateMachine() {};
	~GameStateMachine();

	GameState* currentState();
	void pushState(GameState* newState);
	void changeState(GameState* newState);
	void popState();
};