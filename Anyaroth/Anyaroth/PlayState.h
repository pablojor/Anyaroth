#pragma once
#include "GameState.h"
#include "Layer.h"
#include "Player.h"
#include "MeleeEnemyComponent.h"
#include "DebugDraw.h"
#include "CollisionManager.h"

class Player;

class PlayState : public GameState
{
	private:
		Game* _game = nullptr;
		Player* _player = nullptr;
		Enemy* _enemy = nullptr;
		Layer* _layer = nullptr;
		CollisionManager _colManager;
		DebugDraw _debugger;

	public:
		PlayState(Game* g);
		virtual void update();
		virtual bool handleEvents(SDL_Event& e);
};