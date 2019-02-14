#pragma once
#include "GameState.h"
#include "Layer.h"
#include "Player.h"
#include <Box2D/Box2D.h>

class PlayState : public GameState
{
private:
	b2World* _world = nullptr;
	Player* _player = nullptr;
	Layer* _colLayer = nullptr;

public:
	PlayState(Game* g);
	virtual void update();
	virtual void handleEvents(SDL_Event& e);
};