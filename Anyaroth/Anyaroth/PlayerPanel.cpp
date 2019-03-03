#include "PlayerPanel.h"
#include "Game.h"


PlayerPanel::PlayerPanel(Game* game) : PanelUI(game)
{
	//Inicializamos
	_lifeBar = new LifeBar(game, 5, 5);
	_dashViewer = new DashViewer(game, 5, _lifeBar->getY() + _lifeBar->getH() + 1);
	_weaponryViewer = new WeaponryViewer(game, 5, _dashViewer->getY() + _dashViewer->getH() + 2);
	_ammoViewer = new AmmoViewer(game, 32, _dashViewer->getY() + _dashViewer->getH() + 8);
	_coinsCounter = new CoinsCounter(game, GAME_RESOLUTION_X - 50, 5);

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
