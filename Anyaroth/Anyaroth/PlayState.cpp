#include "PlayState.h"
#include "Game.h"

#include "ExampleObject.h"

PlayState::PlayState(Game* g) : GameState(g)
{
	_stages.push_back(new ExampleObject("Player", g->getTexture("example1")));
	_stages.push_back(new ExampleObject("Enemy", g->getTexture("example1")));
}

void PlayState::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);
}

void PlayState::update()
{
	GameState::update();
}