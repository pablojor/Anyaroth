#include "GameStateMachine.h"

GameState* GameStateMachine::currentState()
{
	return states.top();
}
void GameStateMachine::pushState(GameState* newState)
{
	states.push(newState);
}
void GameStateMachine::changeState(GameState* newState)
{
	states.pop();
	states.push(newState);
}
void GameStateMachine::popState()
{
	states.pop();
}