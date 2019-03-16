#pragma once
#include "GameState.h"
#include "Shop.h"

class Player;

class SafeZoneScene : public GameState
{
	private:
		Player* _player = nullptr;

		Shop* _shop = nullptr;

	public:
		SafeZoneScene(Game* g, Player* ply, string file);
		~SafeZoneScene();

		void loadFromFile(string s);

		virtual void render() const;
		virtual void update(double time);
		virtual bool handleEvents(SDL_Event& e);
};

