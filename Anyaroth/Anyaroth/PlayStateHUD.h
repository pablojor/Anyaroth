#pragma once
#include "Canvas.h"
#include "PlayerPanel.h"
#include "BossPanel.h"
#include "ShopMenu.h"
#include "DialoguePanel.h"
#include "EnemyLifePanel.h"
#include "PopUpPanel.h"
#include "Cursor.h"

class Game;

class PlayStateHUD : public Canvas
{
private:
	PlayerPanel* _playerPanel = nullptr;
	BossPanel* _bossPanel = nullptr;
	ShopMenu* _shopMenu;
	DialoguePanel* _dialoguePanel = nullptr;
	EnemyLifePanel* _enemyLifePanel = nullptr;
	PopUpPanel* _popUpPanel = nullptr;
	Cursor* _cursor = nullptr;

public:
	PlayStateHUD() {}
	PlayStateHUD(Game* g);
	virtual ~PlayStateHUD() {}

	inline PlayerPanel* getPlayerPanel() const { return _playerPanel; }
	inline BossPanel* getBossPanel() const { return _bossPanel; }
	inline ShopMenu* getShop() const { return _shopMenu; }
	inline DialoguePanel* getDialoguePanel() const { return _dialoguePanel; }
	inline EnemyLifePanel* getEnemyLifePanel() const { return _enemyLifePanel; }

	inline void reset() { _enemyLifePanel->reset(); }
	inline PopUpPanel* getPopUpPanel() const { return _popUpPanel; }
	inline Cursor* getCursor() const { return _cursor; }
};