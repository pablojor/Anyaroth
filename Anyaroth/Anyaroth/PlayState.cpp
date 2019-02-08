#include "PlayState.h"
#include "Game.h"

#include "ExampleObject.h"

PlayState::PlayState(Game* g) : GameState(g){
	stages.push_back(new ExampleObject(g->getTexture("Mk")));
}

void PlayState::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);
}

void PlayState::update()
{
	GameState::update();
}