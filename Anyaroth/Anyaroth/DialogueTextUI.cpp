#include "DialogueTextUI.h"



DialogueTextUI::DialogueTextUI(Game* game, string text, Font* font, uint fontSize, int xPos, int yPos, SDL_Color color) :
	TextUI(game, text, font, fontSize, xPos, yPos, color)
{
	
}


DialogueTextUI::~DialogueTextUI()
{
}

void DialogueTextUI::render() const
{
	if (_visible)
		_texture->render(_destRect);
}

void DialogueTextUI::update(double time)
{
	if (_visible)
	{
		if (_character < _textToType.length() && !_textTyped)
		{
			//Tiempos de espera para cada caracter
			switch (_textToType[_character])
			{
			case '.':
				_waitTime = 150;
				break;
			default:
				_waitTime = 20;
				break;
			}

			if (_time > _waitTime)
			{
				_dialogueText.push_back(_textToType[_character]);

				string s(_dialogueText.begin(), _dialogueText.end());
				setText(s);

				//if(_textToType[_character]!=' ')
				//		 play talk sound with random pitch

				_time = 0;
				_character++;
			}
			_time += time;
		}
		else
			_textTyped = true;
	}
}

void DialogueTextUI::type(string text)
{
	_dialogueText.clear();
	_character = 0;
	_textToType = text;
	_textTyped = false;
}
