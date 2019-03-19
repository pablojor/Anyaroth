#pragma once

#include "PanelUI.h"
#include "DialogueTextUI.h"
#include "ImageUI.h"
#include "FramedImageUI.h"
#include "TextUI.h"

class Game;

class DialoguePanel : public PanelUI
{
private:

	ImageUI* _backgroundImage = nullptr;
	FramedImageUI* _faceImage = nullptr;
	ImageUI* _indicatorImage = nullptr;
	TextUI* _nameText = nullptr;
	DialogueTextUI* _dialogueText = nullptr;
public:
	DialoguePanel() {};
	DialoguePanel(Game* game);
	~DialoguePanel() {}

	//inline void updateLifeBar(const int& life, const int& maxLife) { _lifeBar->updateLifeBar(life, maxLife); }
};