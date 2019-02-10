#pragma once
#include "GameState.h"
#include "CollisionManager.h"
#include "Layer.h"
#include "Player.h"

class PlayState : public GameState
{
	private:
		CollisionManager* _colManager = nullptr;

		Player* _player = nullptr;
		Layer* _colLayer = nullptr;
	public:
		
		PlayState(Game* g);
		virtual void update();
		virtual void handleEvents(SDL_Event& e);

};