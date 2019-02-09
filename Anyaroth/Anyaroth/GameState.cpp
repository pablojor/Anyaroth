#include "GameState.h"
#include "Game.h"


GameState::GameState(Game* g) {
	gameptr = g;
}

GameState::~GameState()
{
	for (GameObject* o : stages)
		delete o;
}
void GameState::render() const
{
	for (GameObject* o : stages)
		o->render();
}

void GameState::update()
{
	for (GameObject* o : stages)
		o->update();
}

void GameState::handleEvents(SDL_Event& e)
{
	for (GameObject* o : stages)
		o->handleInput(e);
}