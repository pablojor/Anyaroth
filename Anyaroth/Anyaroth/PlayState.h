#pragma once
#include "GameState.h"
#include "Layer.h"
#include "Player.h"
#include "MeleeEnemyComponent.h"

class Player;

class PlayState : public GameState
{
	private:
		Player* _player = nullptr;
		Layer* _colLayer = nullptr;
		Enemy* _enemy = nullptr;

	public:
		PlayState(Game* g);
		virtual void update();
		virtual void handleEvents(SDL_Event& e);
};