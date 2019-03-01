#include "PlayerPanel.h"
#include "Game.h"


PlayerPanel::PlayerPanel(Game* game) : PanelUI(game)
{
	//Inicializamos
	_lifeBar = new LifeBar(game, game->getTexture("Ammo"), 50, 20);
	_ammoViewer = new AmmoViewer(game, GAME_RESOLUTION_X / 2, GAME_RESOLUTION_Y / 2);
	_coinsCounter = new CoinsCounter(game, GAME_RESOLUTION_X - 50, 5);

	//Asignamos lo que necesite cada quien
	_lifeBar->updateLifeBar(LIFE, MAX_LIFE);
	_ammoViewer->updateAmmoViewer(LIFE, MAX_LIFE);

	//Añadimos al panel
	addChild(_lifeBar);
	addChild(_ammoViewer);
	addChild(_coinsCounter);

}


PlayerPanel::~PlayerPanel()
{
}
