#pragma once

#include "PanelUI.h"
#include "DialogueTextUI.h"
#include "ImageUI.h"
#include "AnimatedImageUI.h"
#include "FramedImageUI.h"
#include "TextUI.h"

class Game;

struct Dialogue
{
	Texture* face = nullptr;
	string name;
	//Voz
	//Sonido especial
	vector<string> conversation;
	vector<int> faces;			//0->feliz, 1->triste, 2->enfadado // esto iria con un enum
};




class DialoguePanel : public PanelUI
{
private:

	AnimatedImageUI* _backgroundImage = nullptr;
	FramedImageUI* _faceImage = nullptr;
	ImageUI* _indicatorImage = nullptr;
	TextUI* _nameText = nullptr;
	DialogueTextUI* _dialogueText = nullptr;

	Dialogue _testDialogue = {};

	Dialogue _dialogue;
	int _currentText = 0;
	bool _isConversating = false;

public:
	DialoguePanel() {};
	DialoguePanel(Game* game);
	~DialoguePanel() {}

	virtual void update(double time);
	virtual void handleEvent(const SDL_Event& event);

	void startDialogue(const Dialogue& dialogue);
	void endDialogue();
	void nextText();
};