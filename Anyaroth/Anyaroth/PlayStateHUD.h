#pragma once
#include "Canvas.h"
#include "PlayerPanel.h"
#include "BossPanel.h"
#include "ShopMenu.h"
#include "DialoguePanel.h"
#include "PopUpPanel.h"

class Game;

class PlayStateHUD : public Canvas
{
private:
	PlayerPanel* _playerPanel = nullptr;
	BossPanel* _bossPanel = nullptr;
	ShopMenu* _shopMenu;
	DialoguePanel* _dialoguePanel = nullptr;
	PopUpPanel* _popUpPanel = nullptr;


public:
	PlayStateHUD() {}
	PlayStateHUD(Game* g);
	virtual ~PlayStateHUD() {}

	inline PlayerPanel* getPlayerPanel() const { return _playerPanel; }
	inline BossPanel* getBossPanel() const { return _bossPanel; }
	inline ShopMenu* getShop() const { return _shopMenu; }
	inline DialoguePanel* getDialoguePanel() const { return _dialoguePanel; }
	inline PopUpPanel* getPopUpPanel() const { return _popUpPanel; }
};