#pragma once

#include "PanelUI.h"
#include "DialogueTextUI.h"

class Game;

class DialoguePanel : public PanelUI
{
private:
	DialogueTextUI* _testDialogue = nullptr;

public:
	DialoguePanel() {};
	DialoguePanel(Game* game);
	~DialoguePanel() {}

	//inline void updateLifeBar(const int& life, const int& maxLife) { _lifeBar->updateLifeBar(life, maxLife); }
};