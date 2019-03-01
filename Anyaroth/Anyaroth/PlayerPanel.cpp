#include "PlayerPanel.h"
#include "Game.h"


PlayerPanel::PlayerPanel(Game* game) : PanelUI(game)
{
	//Inicializamos
	_lifeBar = new LifeBar(game, game->getTexture("Ammo"), 30, 10);
	_ammoViewer = new AmmoViewer(game, 30, 25);
	_weaponryViewer = new WeaponryViewer(game, 30 - 1, 40);
	_coinsCounter = new CoinsCounter(game, GAME_RESOLUTION_X - 50, 10);

	//Asignamos lo que necesite cada quien
	_lifeBar->updateLifeBar(LIFE, MAX_LIFE);
	_ammoViewer->updateAmmoViewer(LIFE, MAX_LIFE);

	//Añadimos al panel
	addChild(_lifeBar);
	addChild(_ammoViewer);
	addChild(_coinsCounter);
	addChild(_weaponryViewer);
}


PlayerPanel::~PlayerPanel()
{
}
