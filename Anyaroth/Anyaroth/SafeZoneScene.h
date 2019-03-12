#pragma once
#include "GameState.h"

class Player;

class SafeZoneScene : public GameState
{
	private:
		Player* _player = nullptr;

	public:
		SafeZoneScene(Game* g, Player* ply) :
			_player(ply), GameState::GameState(g){}
		~SafeZoneScene();

		virtual void render() const;
		virtual void update(double time);
		virtual bool handleEvents(SDL_Event& e);
};

