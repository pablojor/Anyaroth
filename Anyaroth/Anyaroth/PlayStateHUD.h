#pragma once
#include "Canvas.h"
#include "PlayerPanel.h"
#include "BossPanel.h"
#include "Boss3Panel.h"
#include "ShopMenu.h"
#include "DialoguePanel.h"

class Game;

class PlayStateHUD : public Canvas
{
private:
	PlayerPanel* _playerPanel = nullptr;
	BossPanel* _bossPanel = nullptr;
	Boss3Panel* _boss3Panel = nullptr;
	ShopMenu* _shopMenu;
	DialoguePanel* _dialoguePanel = nullptr;

public:
	PlayStateHUD() {}
	PlayStateHUD(Game* g);
	virtual ~PlayStateHUD() {}

	inline PlayerPanel* getPlayerPanel() const { return _playerPanel; }
	inline BossPanel* getBossPanel() const { return _bossPanel; }
	inline Boss3Panel* getBoss3Panel() const { return _boss3Panel; }
	inline ShopMenu* getShop() const { return _shopMenu; }
	inline DialoguePanel* getDialoguePanel() const { return _dialoguePanel; }
};