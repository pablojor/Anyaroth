#include "DialoguePanel.h"
#include "Game.h"


DialoguePanel::DialoguePanel(Game* game) : PanelUI(game)
{

	/************/

	//dialogo de prueba, esto iria leido de un json o algo
	_testDialogue = Dialogue{
		game->getTexture("DialogueFace"),
		"Jagh",
		{ "*Bzzt..Bip, bip..* Hey, ¿qué tal?", "Ajá, con que programando... ya veo...", "¡Pues sigue con eso, chaval! ¡Adew! *Bip*" },
		{0,1,2}
	};

	/***********/


	//Inicializamos
	_backgroundImage = new AnimatedImageUI(game, game->getTexture("DialogueBg"), 3, 192);
	_faceImage = new FramedImageUI(game, game->getTexture("DialogueFace"), _backgroundImage->getX() + 11, _backgroundImage->getY() + 11);
	_indicatorImage = new ImageUI(game, game->getTexture("DialogueIndicator"), _backgroundImage->getW() - 22, _backgroundImage->getY() + 58);
	_nameText = new TextUI(game, " ", game->getFont("ARIAL12"), 12, _faceImage->getW() - 20, _faceImage->getY() - 20, { 145, 255, 255, 255 });

	_dialogueText = new DialogueTextUI(game, " ", game->getFont("ARIAL12"), 12, _faceImage->getW() + 25, _faceImage->getY(), { 255, 255, 255, 255 });

	//Animaciones
	_backgroundImage->addAnim(AnimatedImageUI::Default, 1, false);
	_backgroundImage->addAnim(AnimatedImageUI::End, 8, false);
	_backgroundImage->addAnim(AnimatedImageUI::Start, 8, false);


	_backgroundImage->playAnim(AnimatedImageUI::Default);

	//Ponemos invisible todo inicialmente
	//_backgroundImage->setVisible(false);
	_indicatorImage->setVisible(false);
	_faceImage->setVisible(false);
	_nameText->setVisible(false);

	_dialogueText->setVisible(false);

	setVisible(false);

	//Asignamos lo que necesite cada quien
	////////////////////

	//Añadimos al panel
	addChild(_backgroundImage);
	addChild(_faceImage);
	addChild(_indicatorImage);
	addChild(_nameText);
	addChild(_dialogueText);
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
		_dialogueText->setTextTyped(false);

		//ponemos visible el cuadro de dialogo primero antes que las demas cosas
		setVisible(true);
		_backgroundImage->setVisible(true);

		//comenzamos animación de abrir diálogo
		_backgroundImage->playAnim(AnimatedImageUI::Start);
	}
}

void DialoguePanel::endDialogue()
{
	_dialogue = {};
	_isConversating = false;

	//ponemos invisible todo
	_indicatorImage->setVisible(false);
	_faceImage->setVisible(false);
	_nameText->setVisible(false);
	_dialogueText->setVisible(false);

	//reseteamos lo que había
	_nameText->setText(" ");
	_dialogueText->setText(" ");

	//comenzamos animacion de cerrar diálogo
	_backgroundImage->playAnim(AnimatedImageUI::End);
}

void DialoguePanel::nextText()
{
	if (_isConversating && _dialogue.conversation.size() != 0 && _dialogueText->textTyped())
	{
		_currentText++;
		_indicatorImage->setVisible(false);

		//Si la lista de textos no está vacía, ya se ha escrito entero un texto y éste no es el último, se escribe el siguiente.
		if (_currentText < _dialogue.conversation.size())
		{
			if (_faceImage->getFrame() != _dialogue.faces[_currentText])
				_faceImage->changeFrame(_dialogue.faces[_currentText]);

			_dialogueText->type(_dialogue.conversation[_currentText]);
		}
		else //Si _currentText ya es el último, se termina la conversación y se cierra el diálogo.
		{
			_currentText = 0;

			endDialogue();
		}
	}
}

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

			_dialogueText->setVisible(true);

			//comenzamos dialogo
			_faceImage->changeFrame(_dialogue.faces[_currentText]);
			_dialogueText->type(_dialogue.conversation[0]);
		}

		//Hacer visible indicador cuando termina de escribir el texto
		else if (_isConversating && !_indicatorImage->isVisible() && _dialogueText->textTyped())
		{
			_indicatorImage->setVisible(true);
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