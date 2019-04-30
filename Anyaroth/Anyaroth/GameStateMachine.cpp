#include "GameStateMachine.h"

GameStateMachine::~GameStateMachine()
{
	while (!_states.empty())
		popState();
}

GameState* GameStateMachine::currentState()
{
	if (!_states.empty())
		return _states.top();
}

void GameStateMachine::pushState(GameState* newState)
{
	_states.push(newState);
}

void GameStateMachine::changeState(GameState* newState)
{
	if (!_states.empty()) {
		popState();
		pushState(newState);
	}
	else
		pushState(newState);
}

void GameStateMachine::popState()
{
	delete currentState();
	_states.pop();
}