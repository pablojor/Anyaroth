#include "DialoguePanel.h"
#include "Game.h"
#include <iterator>
#include <sstream>

DialoguePanel::DialoguePanel(Game* game) : PanelUI(game)
{
	//Inicializamos
	_backgroundImage = new AnimatedImageUI(game, game->getTexture("DialogueBg"), 3, 192);
	_faceImage = new FramedImageUI(game, game->getTexture("DialogueFace"), _backgroundImage->getX() + 11, _backgroundImage->getY() + 11);
	_indicatorImage = new AnimatedImageUI(game, game->getTexture("DialogueIndicator"), _backgroundImage->getW() - 22, _backgroundImage->getY() + 58);
	_nameText = new TextUI(game, " ", game->getFont("ARIAL12"), 12, _faceImage->getW() - 20, _faceImage->getY() - 20, { 145, 255, 255, 255 });

	for (int i = 0; i < _lines; i++)
	{
		_dialogueTexts.push_back(new DialogueTextUI(game, " ", game->getFont("ARIAL12"), 12, _faceImage->getW() + 25, _faceImage->getY() - 3 + _gap * i, { 255, 255, 255, 255 }));
		_segments.push_back(" ");
	}
	//Animaciones
	_backgroundImage->addAnim(AnimatedImageUI::Default, 1, false);
	_backgroundImage->addAnim(AnimatedImageUI::End, 8, false);
	_backgroundImage->addAnim(AnimatedImageUI::Start, 8, false);

	_indicatorImage->addAnim(AnimatedImageUI::Idle, 7, true);

	_backgroundImage->playAnim(AnimatedImageUI::Default);
	_indicatorImage->playAnim(AnimatedImageUI::Idle);

	//Ponemos invisible todo inicialmente
	//_backgroundImage->setVisible(false);
	_indicatorImage->setVisible(false);
	_faceImage->setVisible(false);
	_nameText->setVisible(false);

	for (int i = 0; i < _lines; i++)
		_dialogueTexts[i]->setVisible(false);

	setVisible(false);

	//Asignamos lo que necesite cada quien

	//Añadimos al panel
	addChild(_backgroundImage);
	addChild(_faceImage);
	addChild(_indicatorImage);
	addChild(_nameText);

	for (int i = 0; i < _lines; i++)
		addChild(_dialogueTexts[i]);
}

DialoguePanel::~DialoguePanel()
{
	for (int i = 0; i < _lines; i++)
		_dialogueTexts.pop_back();
}

void DialoguePanel::startDialogue(const Dialogue& dialogue)
{
	if (!_isConversating)
	{
		//inicializamos
		_dialogue = dialogue;
		_currentText = 0;
		_isConversating = true;

		//inicializamos cada elemento
		_nameText->setText(_dialogue.name);
		_faceImage->setImage(_dialogue.face);
		for (int i = 0; i < _lines; i++)
		{
			_dialogueTexts[i]->setVoice(_dialogue.voice);
		}

		//si es necesario, troceamos
		//if (_dialogue.conversation[0].size >)
		int i = 1;
		string temp = _dialogue.conversation[0].c_str();
		while (i < _lines && TTF_SizeText(_game->getFont("ARIAL12")->getTTFFont(), temp.c_str(), &_width, nullptr) > _maxWidth)
		{
			
			istringstream iss(temp);
			vector<string> results(istream_iterator<string>{iss},
				istream_iterator<string>());
			
			/*while (temp.substr(0, temp.find(' ')))
			{

			}*/

			i++;
		}
		//ponemos visible el cuadro de dialogo primero antes que las demas cosas
		setVisible(true);
		_backgroundImage->setVisible(true);

		//comenzamos animación de abrir diálogo
		_backgroundImage->playAnim(AnimatedImageUI::Start);

		//REPRODUCIR SONIDO DE ABRIR DIALOGO
		_game->getSoundManager()->playSFX("openDialogue");
	}
}

void DialoguePanel::endDialogue()
{
	_isConversating = false;

	//ponemos invisible todo y reseteamos lo que había
	_indicatorImage->setVisible(false);
	_faceImage->setVisible(false);
	_nameText->setVisible(false);

	_nameText->setText(" ");

	_linesTyped = 0;
	_currentText = 0;

	for (int i = 0; i < _lines; i++)
	{
		_dialogueTexts[i]->setVisible(false);
		_dialogueTexts[i]->setText(" ");
		_dialogueTexts[i]->setTextTyped(false);
	}

	//REPRODUCIR SONIDO ESPECIAL DE FINAL DE DIALOGO
	if (_dialogue.sounds[_currentText] != " ")
		_game->getSoundManager()->playSFX(_dialogue.sounds[_currentText]);

	//comenzamos animacion de cerrar diálogo
	_backgroundImage->playAnim(AnimatedImageUI::End);

	//REPRODUCIR SONIDO DE CERRAR DIALOGO
	_game->getSoundManager()->playSFX("closeDialogue");

	_dialogue = {};
}

void DialoguePanel::nextText()
{
	if (_isConversating && _dialogue.conversation.size() != 0 && _linesTyped == _lines)
	{
		_currentText++;
		_indicatorImage->setVisible(false);
		_linesTyped = 0;

		for (int i = 0; i < _lines; i++)
			_dialogueTexts[i]->setText(" ");

		//Si la lista de textos no está vacía, ya se ha escrito entero un texto y éste no es el último, se escribe el siguiente.
		if (_currentText < _dialogue.conversation.size())
		{
			if (_faceImage->getFrame() != _dialogue.faces[_currentText])
				_faceImage->changeFrame(_dialogue.faces[_currentText]);

			//REPRODUCIR SONIDO DE PASO DE TEXTO DEL DIALOGO
			_game->getSoundManager()->playSFX("example1");
			///ANIMACION DE INDICADOR DE PASO DE TEXTO DEL DIALOGO
			//REPRODUCIR SONIDO ESPECIAL DE TEXTO DEL DIALOGO
			if (_dialogue.sounds[_currentText] != " ")
				_game->getSoundManager()->playSFX(_dialogue.sounds[_currentText]);



			_dialogueTexts[0]->type(_dialogue.conversation[_currentText]);
		}
		else //Si _currentText ya es el último, se termina la conversación y se cierra el diálogo.
			endDialogue();
	}
}

/*bool DialoguePanel::allTextTyped() const
{
	int i = 0;
	while (i < _dialogueTexts.size() && _dialogueTexts[i]->textTyped())
		i++;
	if (i < _dialogueTexts.size())
		return false;
	return true;
}*/

void DialoguePanel::update(double time)
{
	PanelUI::update(time);

	if (_visible)
	{
		//Cuando termine animacion de cerrar dialogo
		if (_backgroundImage->getCurrentAnim() == AnimatedImageUI::End && _backgroundImage->animationFinished())
		{
			_backgroundImage->playAnim(AnimatedImageUI::Default);
			_backgroundImage->setVisible(false);

			setVisible(false);
		}
		//Cuando termine animacion de abrir dialogo
		else if (_backgroundImage->getCurrentAnim() == AnimatedImageUI::Start && _backgroundImage->animationFinished())
		{
			_backgroundImage->playAnim(AnimatedImageUI::Default);

			_faceImage->setVisible(true);
			_nameText->setVisible(true);

			for (int i = 0; i < _lines; i++)
				_dialogueTexts[i]->setVisible(true);

			//REPRODUCIR SONIDO ESPECIAL DE INICIO DE DIALOGO
			if (_dialogue.sounds[_currentText] != " ")
				_game->getSoundManager()->playSFX(_dialogue.sounds[_currentText]);

			//comenzamos dialogo
			_faceImage->changeFrame(_dialogue.faces[_currentText]);
			_dialogueTexts[0]->type(_dialogue.conversation[0]);
		}
		else if (_linesTyped == _lines)
		{
			//Hacer visible indicador cuando termina de escribir el texto
			if (_isConversating && !_indicatorImage->isVisible())
			{
				_indicatorImage->setVisible(true);

			}
		}//Si se ha terminado de escribir una linea, se escribe la siguiente
		else if (_dialogueTexts[_linesTyped]->textTyped())
		{
			_linesTyped++;
			if (_linesTyped != _lines)
				_dialogueTexts[_linesTyped]->type(_segments[_linesTyped]);
		}
	}
}

void DialoguePanel::handleEvent(const SDL_Event& event)
{
	PanelUI::handleEvent(event);

	if (event.type == SDL_KEYDOWN && !event.key.repeat) // Captura solo el primer frame que se pulsa
	{
		if (event.key.keysym.sym == SDLK_x) //EVENTO DE COMENZAR DIALOGO
			startDialogue(_testDialogue);
		else if (event.key.keysym.sym == SDLK_e) //TECLA PARA PASAR DE TEXTO EN EL DIALOGO
			nextText();
	}
}