#include "PlayState.h"
#include "PauseState.h"
#include "Game.h"
#include "BodyComponent.h"
#include "FollowingComponent.h"
#include "checkML.h"

PlayState::PlayState(Game* g) : GameState(g)
{
	_game = g;

	//World
	_debugger.getRenderer(g->getRenderer());
	_debugger.getTexture(g->getTexture("body"));
	_debugger.SetFlags(b2Draw::e_shapeBit);

	//Gestion de colisiones
	g->getWorld()->SetContactListener(&_colManager);
	//g->getWorld()->SetDebugDraw(&_debugger);

	//Tilemap
	_layer = new Layer("Capa de Patrones 1", g->getTexture("tileset"), TILEMAP_PATH + "Nivel1.json", g);
	_layer->addComponent<BodyComponent>();
	_stages.push_back(_layer);

	//Player
	_player = new Player(g->getTexture("Mk"), g);
	_stages.push_back(_player);
}

void PlayState::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
		_game->pushState(new PauseState(_game));
	}
}

void PlayState::update()
{
	GameState::update();
}