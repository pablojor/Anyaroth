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
	string voice;	//Voz
	string name;
	vector<string> conversation;
	vector<int> faces;			//Caras de cada texto (0->feliz, 1->triste, 2->enfadado) // esto iria con un enum
	vector<string> sounds;		//Sonidos de cada texto (" "->sin sonido, "surprise"->sonido de sorpresa etc etc) //Sonido inicio/final de la conversacion
};

class DialoguePanel : public PanelUI
{
private:
	AnimatedImageUI* _backgroundImage = nullptr;
	FramedImageUI* _faceImage = nullptr;
	AnimatedImageUI* _indicatorImage = nullptr;
	TextUI* _nameText = nullptr;

	int _lines = 3;
	int _gap = 10;

	vector<DialogueTextUI*> _dialogueTexts = {};

	Dialogue _testDialogue = {};

	Dialogue _dialogue;
	int _currentText = 0;
	int _linesTyped = 0;
	bool _isConversating = false;

public:
	DialoguePanel() {};
	DialoguePanel(Game* game);
	~DialoguePanel();

	virtual void update(double time);
	virtual void handleEvent(const SDL_Event& event);

	inline bool isConversating() const { return _isConversating; }

	void startDialogue(const Dialogue& dialogue);
	void endDialogue();
	void nextText();

	//bool allTextTyped() const;

};