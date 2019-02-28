#pragma once
#include "Canvas.h"
#include "PlayerPanel.h"

class Game;

class PlayStateHUD : public Canvas
{
	private:
		PlayerPanel* _playerPanel;
	public:
		PlayStateHUD() {};
		PlayStateHUD(Game* g);
		virtual ~PlayStateHUD() {};
};

