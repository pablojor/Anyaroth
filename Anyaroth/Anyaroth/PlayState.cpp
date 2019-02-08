#include "PlayState.h"
#include "Game.h"
#include "CollisionManager.h"

PlayState::PlayState(Game* g) : GameState(g)
{
	_ex = new ExampleObject(Vector2D(720 / 2, 480 / 2), g->getTexture("example1"));
	_ex2 = new ExampleObject2(Vector2D(130, 100), g->getTexture("example2"));
	_stages.push_back(_ex);
	_stages.push_back(_ex2);
}

void PlayState::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);
}

void PlayState::update()
{
	GameState::update();
}