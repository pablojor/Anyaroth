#pragma once
#include "PanelUI.h"
#include "ImageUI.h"
#include "ButtonUI.h"

class Player;

class DepotPanel : public PanelUI
{
	private:
		Player* _player = nullptr;
		ImageUI* _depotFrame = nullptr;
		ImageUI* _equipmentFrame = nullptr;
		ButtonUI* _exitButton = nullptr;

		ImageUI* _firstWeapon = nullptr;
		ImageUI* _secondWeapon = nullptr;
		ImageUI* _meleeWeapon = nullptr;

	public:
		DepotPanel(Game* game, Player* player);
};

