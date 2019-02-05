#include "GameState.h"

GameState::~GameState()
{
	for (GameObject* o : stages)
		delete o;
}
void GameState::render() const
{
	for (GameObject* o : stages)
		o->render(0);
}

void GameState::update()
{
	for (GameObject* o : stages)
		o->update(0);
}

void GameState::handleEvents(SDL_Event& e)
{
	for (GameObject* o : stages)
		o->handleInput(0,e);
}