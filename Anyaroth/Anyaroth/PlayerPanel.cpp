#include "PlayerPanel.h"
#include "Game.h"


PlayerPanel::PlayerPanel(Game* game) : PanelUI(game)
{
	//Inicializamos
	_lifeBar = new LifeBar(game, game->getTexture("Ammo"), 50, 20);
	_ammoViewer = new TextUI(game, "Ammo: " + to_string(29), game->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_coinsCounter = new CoinsCounter(game,GAME_RESOLUTION_X - 50, 5);

	//Asignamos lo que necesite cada quien
	_lifeBar->setLifeAndMaxLife(&LIFE, &MAX_LIFE);

	//Añadimos al panel
	addChild(_lifeBar);
	addChild(_ammoViewer);
	addChild(_coinsCounter);

}


PlayerPanel::~PlayerPanel()
{
}
