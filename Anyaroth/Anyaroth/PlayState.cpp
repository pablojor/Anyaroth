#include "PlayState.h"
#include "Game.h"

#include "ExampleObject.h"

PlayState::PlayState(Game* g) : GameState(g)
{
	_stages.push_back(new ExampleObject(Vector2D(720 / 2, 480 / 2), g->getTexture("example1")));
	_stages.push_back(new ExampleObject(Vector2D(130, 100), g->getTexture("example2")));
}

void PlayState::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);
}

void PlayState::update()
{
	GameState::update();
}