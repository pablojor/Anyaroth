#pragma once

#include "TextUI.h"
#include <vector>

class DialogueTextUI : public TextUI
{
private:
	int _character = 0;

	double _waitTime;
	double _time = 0;

	string _textToType = "Sans al habla... Esto es una prueba. Repito. Esto es una maldita prueba.";
	vector<char> _dialogueText;

	bool _textTyped = false;
public:
	DialogueTextUI(Game* game, string text, Font* font, uint fontSize = 12, int xPos = 0, int yPos = 0, SDL_Color color = { 0, 0, 0, 255 });
	virtual ~DialogueTextUI();

	virtual void render() const;
	virtual void update(double time);

	void type(string text);

	inline bool textTyped() const { return _textTyped; }
};

