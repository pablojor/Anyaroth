#include "GameStateMachine.h"

GameState* GameStateMachine::currentState()
{
	return _states.top();
}
void GameStateMachine::pushState(GameState* newState)
{
	_states.push(newState);
}
void GameStateMachine::changeState(GameState* newState)
{
	_states.pop();
	_states.push(newState);
}
void GameStateMachine::popState()
{
	_states.pop();
}