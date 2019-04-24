#include "PlayerPanel.h"
#include "Game.h"

PlayerPanel::PlayerPanel(Game* game) : PanelUI(game)
{
	//Inicializamos
	_lifeFrame = new ImageUI(game, game->getTexture("LifeBar"), 3, 3);
	_lifeBar = new LifeBar(game, "LifeBarMask", 25, 6);
	_lifeBar->setInUse(true);

	_dashViewer = new DashViewer(game, 3, _lifeFrame->getY() + _lifeFrame->getH() + 3);

	_weaponryViewer = new WeaponryViewer(game, 3, CAMERA_RESOLUTION_Y);
	_ammoViewer = new AmmoViewer(game, 45, CAMERA_RESOLUTION_Y - 34);

	_coinsCounter = new CoinsCounter(game, CAMERA_RESOLUTION_X - 30, 3);

	_deathText = new TextUI(game, "YOU FAILED", game->getFont("ARIAL12"), 50, CAMERA_RESOLUTION_X / 2 - 50, CAMERA_RESOLUTION_Y / 2 - 10, { 255,0,0,1 });
	_deathText->setVisible(false);

	//Añadimos al panel
	addChild(_lifeFrame);
	addChild(_lifeBar);
	addChild(_ammoViewer);
	addChild(_coinsCounter);
	addChild(_weaponryViewer);
	addChild(_dashViewer);
	addChild(_deathText);
}