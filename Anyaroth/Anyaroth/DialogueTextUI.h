#pragma once

#include "TextUI.h"
#include <vector>

class DialogueTextUI : public TextUI
{
private:
	int _character = 0;

	double _waitTime;
	double _time = 0;

	string _voice;

	string _textToType = " ";
	vector<char> _dialogueTexts;

	bool _textTyped = false;
public:
	DialogueTextUI(Game* game, string text, Font* font, uint fontSize = 12, int xPos = 0, int yPos = 0, SDL_Color color = { 0, 0, 0, 255 });
	virtual ~DialogueTextUI();

	virtual void update(double time);

	void type(string text);

	inline void setVoice(const string& s) { _voice = s; }

	inline bool textTyped() const { return _textTyped; }

	inline void setTextTyped(const bool& b) { _textTyped = b; }
};

