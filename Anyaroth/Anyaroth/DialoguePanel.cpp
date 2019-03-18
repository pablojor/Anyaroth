#include "DialoguePanel.h"
#include "Game.h"

DialoguePanel::DialoguePanel(Game* game) : PanelUI(game)
{
	//Inicializamos
	//_lifeBar = new LifeBar(game, 5, 5);


	_testDialogue = new DialogueTextUI(game, "00", game->getFont("ARIAL12"), 12, 150, 50, { 255, 255, 255, 255 });



	//Asignamos lo que necesite cada quien
	//updateDashViewer(5);

	//Añadimos al panel
	//addChild(_lifeBar);
	addChild(_testDialogue);
}