#pragma once
#include <stack>
#include "GameState.h"

class GameStateMachine
{
private:
	stack <GameState*> _states;
	bool _hasToInit = true;

public:
	GameStateMachine() {};
	~GameStateMachine();

	GameState* currentState();
	void pushState(GameState* newState);
	void changeState(GameState* newState);
	void popState();
	inline bool hasToInit() const { return _hasToInit; }
	inline void setInitialited() { _hasToInit = false; }
};