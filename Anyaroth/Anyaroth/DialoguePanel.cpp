#include "DialoguePanel.h"
#include "Game.h"


DialoguePanel::DialoguePanel(Game* game) : PanelUI(game)
{
	//Inicializamos
	//_lifeBar = new LifeBar(game, 5, 5);

	_backgroundImage = new ImageUI(game, game->getTexture("DialogueBg"), 3, 192);
	_faceImage = new FramedImageUI(game, game->getTexture("DialogueFace"), _backgroundImage->getX() + 11, _backgroundImage->getY() + 11);
	_indicatorImage = new ImageUI(game, game->getTexture("DialogueIndicator"), _backgroundImage->getW() - 22, _backgroundImage->getY() + 58);
	_nameText = new TextUI(game, "Mk:", game->getFont("ARIAL12"), 12, _faceImage->getW() - 20, _faceImage->getY() - 20 , { 255, 255, 255, 255 });
	_dialogueText = new DialogueTextUI(game, "Mensajito", game->getFont("ARIAL12"), 12, _faceImage->getW() + 25, _faceImage->getY(), { 255, 255, 255, 255 });


	_indicatorImage->setVisible(false);

	//Asignamos lo que necesite cada quien
	//updateDashViewer(5);

	//Añadimos al panel
	//addChild(_lifeBar);
	addChild(_backgroundImage);
	addChild(_faceImage);
	addChild(_indicatorImage);
	addChild(_nameText);
	addChild(_dialogueText);
}