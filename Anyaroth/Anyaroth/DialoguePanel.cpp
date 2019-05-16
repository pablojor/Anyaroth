#include "DialoguePanel.h"
#include "Game.h"
#include "GameManager.h"
#include <iterator>
#include <sstream>

DialoguePanel::DialoguePanel(Game* game) : PanelUI(game)
{
	//Inicializamos
	_backgroundImage = new AnimatedImageUI(game, game->getTexture("DialogueBg"), 0, 188);
	_faceImage = new FramedImageUI(game, game->getTexture("NPC1Face"), _backgroundImage->getX() + 14, _backgroundImage->getY() + 13);
	_indicatorImage = new AnimatedImageUI(game, game->getTexture("DialogueIndicator"), _backgroundImage->getW() - 22, _backgroundImage->getY() + 61);
	_nameBackground = new AnimatedImageUI(game, game->getTexture("NameBg"), 0, 168);
	_nameText = new TextUI(game, " ", game->getFont("ARIAL12"), 12, _faceImage->getX(), _faceImage->getY() - 29, { 145, 255, 255, 255 });

	_indicatorText = new TextUI(game, "Press E", game->getFont("ARIAL12"), 12, 0, 0, { 255,255,255,255 });
	_indicatorText->setScale(0.5);
	_indicatorText->setPosition(_indicatorImage->getX() + _indicatorImage->getW() / 2 - _indicatorText->getW() / 2, _indicatorImage->getY() - _indicatorImage->getH());

	for (int i = 0; i < _lines; i++)
	{
		_dialogueTexts.push_back(new DialogueTextUI(game, " ", game->getFont("ARIAL12"), 12, _faceImage->getW() + 25, _faceImage->getY() - 3 + _gap * i, { 255, 255, 255, 255 }));
		_segments.push_back(" ");
	}
	//Animaciones
		//Background
	_backgroundImage->addAnim(AnimatedImageUI::Default, 1, false);
	_backgroundImage->addAnim(AnimatedImageUI::End, 10, false);
	_backgroundImage->addAnim(AnimatedImageUI::Start, 10, false);
	//Background name
	_nameBackground->addAnim(AnimatedImageUI::Default, 1, false);
	_nameBackground->addAnim(AnimatedImageUI::End, 7, false);
	_nameBackground->addAnim(AnimatedImageUI::Start, 7, false);
	//Indicator
	_indicatorImage->addAnim(AnimatedImageUI::Idle, 7, true);

	_backgroundImage->playAnim(AnimatedImageUI::Default);
	_nameBackground->playAnim(AnimatedImageUI::Default);
	_indicatorImage->playAnim(AnimatedImageUI::Idle);

	//Ponemos invisible todo inicialmente
	//_nameBackground->setVisible(false);
	_indicatorImage->setVisible(false);
	_indicatorText->setVisible(false);
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
	addChild(_indicatorText);
	addChild(_nameBackground);
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
		_linesTyped = 0;
		//inicializamos
		_dialogue = dialogue;
		_opened = true;
		_currentText = 0;
		GameManager::getInstance()->setOnDialogue(true);

		if (_dialogue.conversation.size() <= 0)
			_dialogue = { nullptr,"","Default",{"Dialogue not found"},{0},{ "Default" } };

		//inicializamos cada elemento
		if (_dialogue.name != "")
		{
			_nameText->setText(_dialogue.name);
			_nameBackground->setVisible(true);
		}
		else
		{
			_nameBackground->setVisible(false);
			_nameText->setVisible(false);
		}

		if (_dialogue.face != nullptr) {
			_faceImage->setImage(_dialogue.face);
			_maxWidth = 350;
		}
		else
		{
			_faceImage->setVisible(false);
			_maxWidth = 280;
		}

		for (int i = 0; i < _lines; i++)
		{
			_dialogueTexts[i]->setVoice(_dialogue.voice);
		}

		//si es necesario, troceamos el texto
		chopTextIfNecesary(_dialogue.conversation[0]);
		//ponemos visible el cuadro de dialogo primero antes que las demas cosas
		setVisible(true);
		_backgroundImage->setVisible(true);

		//comenzamos animación de abrir diálogo
		_backgroundImage->playAnim(AnimatedImageUI::Start);
		_nameBackground->playAnim(AnimatedImageUI::Start);

		if (!_keepLastLine)
			_game->getSoundManager()->playSFX("openDialogue");
	}
}

void DialoguePanel::endDialogue()
{
	if (_isConversating)
	{
		_isConversating = false;
		GameManager::getInstance()->setOnDialogue(false);

		//ponemos invisible todo y reseteamos lo que había
		_indicatorImage->setVisible(false);
		_indicatorText->setVisible(false);
		_faceImage->setVisible(false);
		_nameText->setVisible(false);

		_nameText->setText(" ");

		_linesTyped = 0;
		_currentText = 0;

		for (int i = 0; i < _lines; i++)
		{
			_dialogueTexts[i]->setVisible(false);
			_dialogueTexts[i]->type(" ");
			_dialogueTexts[i]->completeLine();
			_dialogueTexts[i]->setTextTyped(false);
			_segments[i] = " ";
		}

		//REPRODUCIR SONIDO ESPECIAL DE FINAL DE DIALOGO
		if (_currentText < _dialogue.sounds.size() && _dialogue.sounds[_currentText] != " ")
			_game->getSoundManager()->playSFX(_dialogue.sounds[_currentText]);

		//comenzamos animacion de cerrar diálogo
		_backgroundImage->playAnim(AnimatedImageUI::End);
		_nameBackground->playAnim(AnimatedImageUI::End);
		//REPRODUCIR SONIDO DE CERRAR DIALOGO
		_game->getSoundManager()->playSFX("closeDialogue");

		_dialogue = {};
	}
}

void DialoguePanel::nextText()
{
	if (_isConversating && _dialogue.conversation.size() != 0 && _linesTyped == _lines && _currentText + 1 < _dialogue.conversation.size())
	{
		_currentText++;
		_indicatorImage->setVisible(false);
		_indicatorText->setVisible(false);
		_linesTyped = 0;

		for (int i = 0; i < _lines; i++)
		{
			_dialogueTexts[i]->setText(" ");
			_segments[i] = " ";
		}

		//Si la lista de textos no está vacía, ya se ha escrito entero un texto y éste no es el último, se escribe el siguiente.
		if (_currentText < _dialogue.conversation.size())
		{
			if (_currentText < _dialogue.faces.size() && _faceImage->getFrame() != _dialogue.faces[_currentText])
				_faceImage->changeFrame(_dialogue.faces[_currentText]);

			//REPRODUCIR SONIDO DE PASO DE TEXTO DEL DIALOGO
			_game->getSoundManager()->playSFX("example1");
			///ANIMACION DE INDICADOR DE PASO DE TEXTO DEL DIALOGO
			//REPRODUCIR SONIDO ESPECIAL DE TEXTO DEL DIALOGO
			if (_currentText<_dialogue.sounds.size() && _dialogue.sounds[_currentText] != " ")
				_game->getSoundManager()->playSFX(_dialogue.sounds[_currentText]);

			//si es necesario, troceamos el texto
			chopTextIfNecesary(_dialogue.conversation[_currentText]);

			_dialogueTexts[0]->type(_segments[0]);
			//_dialogueTexts[0]->type(_dialogue.conversation[_currentText]);
		}
		else if(!_keepLastLine) //Si _currentText ya es el último, se termina la conversación y se cierra el diálogo.
			endDialogue();
	}
	else if (!_keepLastLine) //Si _currentText ya es el último, se termina la conversación y se cierra el diálogo.
		endDialogue();
}

void DialoguePanel::chopTextIfNecesary(string text)
{
	string temp = text.c_str();

	TTF_SizeText(_game->getFont("ARIAL12")->getTTFFont(), temp.c_str(), &_width, nullptr);
	if (_width > _maxWidth)
	{
		int i = 0;
		bool finish = false;
		while (i < _lines && !finish)
		{

			istringstream iss(temp);
			vector<string> results(istream_iterator<string>{iss},
				istream_iterator<string>());

			string s = "";
			int j = 0;
			TTF_SizeText(_game->getFont("ARIAL12")->getTTFFont(), s.c_str(), &_width, nullptr);
			while (j < results.size() && _width < _maxWidth)
			{
				s += results[j];
				s += " ";
				TTF_SizeText(_game->getFont("ARIAL12")->getTTFFont(), s.c_str(), &_width, nullptr);
				j++;
			}

			_segments[i] = s;

			if (j < results.size())
			{
				temp = temp.substr(s.size());
				TTF_SizeText(_game->getFont("ARIAL12")->getTTFFont(), temp.c_str(), &_width, nullptr);
			}
			else
			{
				finish = true;
			}

			i++;
		}
	}
	else
		_segments[0] = text;
}

void DialoguePanel::completeLines()
{
	for (int i = 0; i < _lines; i++) {
		_dialogueTexts[i]->type(_segments[i]);
		_dialogueTexts[i]->completeLine();
	}

	_linesTyped = _lines;
}

void DialoguePanel::update(double deltaTime)
{
	PanelUI::update(deltaTime);

	if (_visible)
	{
		//Cuando termine animacion de cerrar dialogo (END DIALOGUE)
		if (_backgroundImage->getCurrentAnim() == AnimatedImageUI::End && (_backgroundImage->animationFinished() || _keepLastLine))
		{
			_backgroundImage->playAnim(AnimatedImageUI::Default);
			_nameBackground->playAnim(AnimatedImageUI::Default);
			_backgroundImage->setVisible(false);
			_nameBackground->setVisible(false);

			_keepLastLine = false;
			_opened = false;
			setVisible(false);
		}
		//Cuando termine animacion de abrir dialogo (START DIALOGUE)
		else if ((_keepLastLine && _backgroundImage->getCurrentAnim() != AnimatedImageUI::Default) || (_backgroundImage->getCurrentAnim() == AnimatedImageUI::Start && _backgroundImage->animationFinished()))
		{
			_isConversating = true;
			_backgroundImage->playAnim(AnimatedImageUI::Default);
			_nameBackground->playAnim(AnimatedImageUI::Default);

			if (_dialogue.face != nullptr)
				_faceImage->setVisible(true);
			if (_dialogue.name != "")
			{
				_nameText->setVisible(true);
				_nameBackground->setVisible(true);
			}

			for (int i = 0; i < _lines; i++)
				_dialogueTexts[i]->setVisible(true);

			//REPRODUCIR SONIDO ESPECIAL DE INICIO DE DIALOGO
			if (_dialogue.sounds[_currentText] != " ")
				_game->getSoundManager()->playSFX(_dialogue.sounds[_currentText]);

			//comenzamos dialogo
			_faceImage->changeFrame(_dialogue.faces[_currentText]);
			_dialogueTexts[0]->type(_segments[0]);
		}
		else if (_linesTyped == _lines)
		{
			//Hacer visible indicador cuando termina de escribir el texto
			if (_isConversating && !_indicatorImage->isVisible())
			{
				if (!_keepLastLine || (_keepLastLine && _currentText != _dialogue.conversation.size() - 1))
				{
					_indicatorImage->setVisible(true);
					_indicatorText->setVisible(true);
				}
			}

		}//Si se ha terminado de escribir una linea, se escribe la siguiente
		else if (_dialogueTexts[_linesTyped]->textTyped())
		{
			_linesTyped++;
			if (_linesTyped != _lines)
				_dialogueTexts[_linesTyped]->type(_segments[_linesTyped]);
		}

		//Cambio de texto dependiendo de los controles
		if (_game->isJoystick()) {
			_indicatorText->setText("Press A");
			_indicatorText->setScale(0.5);
			_indicatorText->setPosition(_indicatorImage->getX() + _indicatorImage->getW() / 2 - _indicatorText->getW() / 2, _indicatorImage->getY() - _indicatorImage->getH());
		}
		else {
			_indicatorText->setText("Press E");
			_indicatorText->setScale(0.5);
			_indicatorText->setPosition(_indicatorImage->getX() + _indicatorImage->getW() / 2 - _indicatorText->getW() / 2, _indicatorImage->getY() - _indicatorImage->getH());
		}
	}
}

bool DialoguePanel::handleEvent(const SDL_Event& event)
{
	bool handled = PanelUI::handleEvent(event);

	if (!handled && _opened)
	{
		if ((event.type == SDL_KEYDOWN) || event.type == SDL_CONTROLLERBUTTONDOWN) // Captura solo el primer frame que se pulsa
		{
			if ((event.key.keysym.sym == SDLK_e && !event.key.repeat) || event.jbutton.button == SDL_CONTROLLER_BUTTON_A) //TECLA PARA PASAR DE TEXTO EN EL DIALOGO
				if (_linesTyped != _lines && _isConversating)
					completeLines();
				else if (_linesTyped == _lines && _isConversating)
					nextText();
		}
	}
	return handled;
}