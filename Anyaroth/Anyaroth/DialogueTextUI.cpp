#include "DialogueTextUI.h"
#include "Game.h"


DialogueTextUI::DialogueTextUI(Game* game, string text, Font* font, uint fontSize, int xPos, int yPos, SDL_Color color) :
	TextUI(game, text, font, fontSize, xPos, yPos, color)
{

}


DialogueTextUI::~DialogueTextUI()
{
}

void DialogueTextUI::update(double deltaTime)
{
	if (_visible)
	{
		if (_character < _textToType.length() && !_textTyped)
		{
			//Tiempos de espera para cada caracter
			switch (_textToType[_character])
			{
			case '.':
				_waitTime = 150; //Poner parámetro aquí para la velocidad de reproduccion
				break;
			default:
				_waitTime = 20;
				break;
			}

			if (_time > _waitTime)
			{
				_dialogueTexts.push_back(_textToType[_character]);

				string s(_dialogueTexts.begin(), _dialogueTexts.end());
				setText(s);

				//reproducir sonido cuando la letra no es un espacio
				if (_textToType[_character] != ' ')
				{
					_game->getSoundManager()->playSFX(_voice);
				}

				_time = 0;
				_character++;
			}
			_time += deltaTime;
		}
		else
			_textTyped = true;
	}
}

void DialogueTextUI::type(string text)
{
	_dialogueTexts.clear();
	_character = 0;
	_textToType = text;
	_textTyped = false;
}

void DialogueTextUI::completeLine()
{
	_textTyped = true;

	while (_character < _textToType.size())
	{
		_dialogueTexts.push_back(_textToType[_character]);
		_character++;
	}
	string s(_dialogueTexts.begin(), _dialogueTexts.end());
	setText(s);
}
