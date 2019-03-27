#include "PlayerPanel.h"
#include "Game.h"

PlayerPanel::PlayerPanel(Game* game) : PanelUI(game)
{
	//Inicializamos
	_marco = new ImageUI(game, game->getTexture("LifeBar"), 3, 3);
	_lifeBar = new LifeBar(game, "LifeBarMask", 25, 6);

	_dashViewer = new DashViewer(game, 3, _marco->getY() + _marco->getH() + 3);

	_weaponryViewer = new WeaponryViewer(game, 3, CAMERA_RESOLUTION_Y);
	_ammoViewer = new AmmoViewer(game, 45, CAMERA_RESOLUTION_Y - 34);

	_coinsCounter = new CoinsCounter(game, CAMERA_RESOLUTION_X - 30, 3);

	_button = new ButtonUI(game, game->getTexture("Button"), CAMERA_RESOLUTION_X / 2, CAMERA_RESOLUTION_Y / 2);
	_button->setFrames(0, 1, 2, 3);

	//Añadimos al panel
	addChild(_marco);
	addChild(_lifeBar);
	addChild(_ammoViewer);
	addChild(_coinsCounter);
	addChild(_weaponryViewer);
	addChild(_dashViewer);
	
	addChild(_button);
}