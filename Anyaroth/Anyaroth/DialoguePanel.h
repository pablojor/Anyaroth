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
	AnimatedImageUI* _nameBackground = nullptr;
	FramedImageUI* _faceImage = nullptr;
	AnimatedImageUI* _indicatorImage = nullptr;
	TextUI* _indicatorText = nullptr;
	TextUI* _nameText = nullptr;

	//Constantes
	int _lines = 4;
	int _gap = 14;
	int _maxWidth = 350;

	vector<string> _segments;
	int _width;

	vector<DialogueTextUI*> _dialogueTexts = {};

	Dialogue _testDialogue = {};

	Dialogue _dialogue;
	int _currentText = 0;
	int _linesTyped = 0;

	bool _isConversating = false;
	bool _opened = false;
	bool _keepLastLine = false;

public:
	DialoguePanel() {};
	DialoguePanel(Game* game);
	~DialoguePanel();

	virtual void update(double deltaTime);
	virtual bool handleEvent(const SDL_Event& event);

	inline bool isConversating() const { return _isConversating; }
	inline bool isOpened() const { return _opened; }
	inline bool conversationEnd() const { return _currentText == _dialogue.conversation.size() - 1; }
	inline bool conversationRealEnd() const { return _currentText == _dialogue.conversation.size(); }

	inline void stopAtLastLineShown(bool b) { _keepLastLine = b; }

	void startDialogue(const Dialogue& dialogue);
	void endDialogue();
	void nextText();
	void chopTextIfNecesary(string text);
	void completeLines();
};