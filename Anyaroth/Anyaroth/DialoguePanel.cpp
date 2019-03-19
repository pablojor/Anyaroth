#include "DialoguePanel.h"
#include "Game.h"


DialoguePanel::DialoguePanel(Game* game) : PanelUI(game)
{

	//dialogo de prueba, esto iria leido de un json o algo
	_testDialogue = Dialogue{
		game->getTexture("DialogueFace"),
		"Jagh",
		{ "*Bzzt..Bip, bip..* Hey, ¿qué tal?", "Ajá, con que programando... ya veo...", "¡Pues sigue con eso, chaval! ¡Adew! *Bip*" },
		{0,1,2}
	};

	//Inicializamos
	_backgroundImage = new AnimatedImageUI(game, game->getTexture("DialogueBg"), 3, 192);
	_faceImage = new FramedImageUI(game, game->getTexture("DialogueFace"), _backgroundImage->getX() + 11, _backgroundImage->getY() + 11);
	_indicatorImage = new ImageUI(game, game->getTexture("DialogueIndicator"), _backgroundImage->getW() - 22, _backgroundImage->getY() + 58);
	_nameText = new TextUI(game, " ", game->getFont("ARIAL12"), 12, _faceImage->getW() - 20, _faceImage->getY() - 20, { 145, 255, 255, 255 });

	_dialogueText = new DialogueTextUI(game, " ", game->getFont("ARIAL12"), 12, _faceImage->getW() + 25, _faceImage->getY(), { 255, 255, 255, 255 });


	_backgroundImage->addAnim(AnimatedImageUI::Default, 1, false);
	_backgroundImage->addAnim(AnimatedImageUI::End, 8, false);
	_backgroundImage->addAnim(AnimatedImageUI::Start, 8, false);


	_backgroundImage->playAnim(AnimatedImageUI::Default);



	//Desactivamos todo
	//_backgroundImage->setVisible(false);
	_indicatorImage->setVisible(false);
	_faceImage->setVisible(false);
	_nameText->setVisible(false);

	_dialogueText->setVisible(false);

	setVisible(false);


	//Asignamos lo que necesite cada quien
	//updateDashViewer(5);

	//Añadimos al panel
	addChild(_backgroundImage);
	addChild(_faceImage);
	addChild(_indicatorImage);
	addChild(_nameText);
	addChild(_dialogueText);
}

void DialoguePanel::startDialogue(const Dialogue& dialogue)
{
	_dialogue = dialogue;
	_currentText = 0;

	//inicializamos
	_nameText->setText(_dialogue.name);
	_faceImage->setImage(_dialogue.face);




	_backgroundImage->playAnim(AnimatedImageUI::Start);



	//ponemos visible todo
	/*_indicatorImage->setVisible(true);
	_faceImage->setVisible(true);
	_nameText->setVisible(true);

	_dialogueText->setVisible(true);*/

	_isConversating = true;

	setVisible(true);

}

void DialoguePanel::endDialogue()
{
	_dialogue = {};

	//limpiamos lo que hay actualmente
	//_nameText->setText("");
	//_dialogueText->setText("");
	//_faceImage->

	//ponemos invisible todo
	_indicatorImage->setVisible(false);
	_faceImage->setVisible(false);
	_nameText->setVisible(false);

	_dialogueText->setVisible(false);


	_backgroundImage->playAnim(AnimatedImageUI::End);

	//setVisible(false);

	_isConversating = false;

	//_dialogueText->type(_dialogue.conversation[0]);
}

void DialoguePanel::nextText()
{
	if (_dialogue.conversation.size() != 0 && _dialogueText->textTyped())
	{

		_currentText++;
		_indicatorImage->setVisible(false);

		//Si la lista de textos no está vacía, ya se ha escrito entero un texto y éste no es el último, se escribe el siguiente.
		if (_currentText < _dialogue.conversation.size())
		{

			//_currentText++;

			if (_faceImage->getFrame() != _dialogue.faces[_currentText])
				_faceImage->changeFrame(_dialogue.faces[_currentText]);

			_dialogueText->type(_dialogue.conversation[_currentText]);

		}
		else //Si _currentText ya es el último, se termina la conversación y se cierra el diálogo.
		{
			_currentText = 0;
			//_backgroundImage->playAnim(DialogueEnd);
			//se pone en invisible todo el panel de diálogo

			endDialogue();
		}
	}

}

void DialoguePanel::update(double time)
{
	PanelUI::update(time);

	if (_visible)
	{
		//Cuando termine animacion
		if (_backgroundImage->getCurrentAnim() == AnimatedImageUI::End && _backgroundImage->animationFinished())
		{
			_backgroundImage->playAnim(AnimatedImageUI::Default);
			_backgroundImage->setVisible(false);
		}
		//Cuando termine animacion
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
		else if (_isConversating &&!_indicatorImage->isVisible() && _dialogueText->textTyped())
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
		if (event.key.keysym.sym == SDLK_x && !_isConversating)
			startDialogue(_testDialogue);
		else if (event.key.keysym.sym == SDLK_e && _isConversating)
			nextText();
	}
}