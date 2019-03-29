#pragma once
#include "PanelUI.h"
#include "ImageUI.h"
#include "ButtonUI.h"

class Player;

class DepotPanel : public PanelUI
{
	private:
		Player* _player = nullptr;
		ImageUI* frame = nullptr;
		ButtonUI* _exitButton = nullptr;

	public:
		DepotPanel(Game* game, Player* ply);
		virtual ~DepotPanel();
};

