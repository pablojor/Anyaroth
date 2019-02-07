#include "PlayState.h"
#include "Game.h"
#include "Layer.h"

PlayState::PlayState(Game* g)  :GameState(g)
{
	stages.push_back(new Layer(2, g->getTexture("tileset"), TILEMAP_PATH+"Prueba.json"));
};

void PlayState::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);
}

void PlayState::update()
{
	GameState::update();
}