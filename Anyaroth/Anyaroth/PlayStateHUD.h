#pragma once
#include "Canvas.h"
#include "PlayerPanel.h"

class Game;

class PlayStateHUD : public Canvas
{
	private:
		PlayerPanel* _playerPanel = nullptr;
		//BossPanel* _bossPanel = nullptr;
	public:
		PlayStateHUD() {};
		PlayStateHUD(Game* g);
		virtual ~PlayStateHUD() {};

		inline PlayerPanel* getPlayerPanel() { return _playerPanel; }
		//inline BossPanel* getBossPanel() { return _bossPanel; }
};

