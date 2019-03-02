#include "PlayerPanel.h"
#include "Game.h"


PlayerPanel::PlayerPanel(Game* game) : PanelUI(game)
{
	//Inicializamos
	_lifeBar = new LifeBar(game, game->getTexture("Ammo"), 30, 10);
	_ammoViewer = new AmmoViewer(game, 30, 25);
	_weaponryViewer = new WeaponryViewer(game, 30 - 1, 40);
	_coinsCounter = new CoinsCounter(game, GAME_RESOLUTION_X - 50, 10);
	_dashViewer = new DashViewer(game, 0, 0);

	//Asignamos lo que necesite cada quien
	updateDashViewer(5);

	//Añadimos al panel
	addChild(_lifeBar);
	addChild(_ammoViewer);
	addChild(_coinsCounter);
	addChild(_weaponryViewer);
	addChild(_dashViewer);
}


PlayerPanel::~PlayerPanel()
{
}
