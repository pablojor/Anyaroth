#include "PlayerPanel.h"
#include "Game.h"

#include <sstream>

PlayerPanel::PlayerPanel(Game* game) : PanelUI(game)
{
	//Inicializamos
	_lifeFrame = new ImageUI(game, game->getTexture("LifeBar"), 3, 3);
	_lifeBar = new LifeBar(game, "LifeBarMask", 25, 6);
	_lifeBar->setInUse(true);
	_lifeText = new TextUI(game, "000HP / 000HP", game->getFont("ARIAL12"), 12, 0, 0, { 255,255,255,255 });
	_lifeText->setScale(0.45f);
	_lifeText->setPosition(_lifeFrame->getX() + _lifeFrame->getW() - _lifeText->getW() - 7, _lifeFrame->getY() + 2 * _lifeFrame->getH() / 3 - 3);

	_dashViewer = new DashViewer(game, 3, _lifeFrame->getY() + _lifeFrame->getH() + 3);

	_weaponryViewer = new WeaponryViewer(game, 3, CAMERA_RESOLUTION_Y);
	_ammoViewer = new AmmoViewer(game, 45, CAMERA_RESOLUTION_Y - 34);

	_coinsCounter = new CoinsCounter(game, CAMERA_RESOLUTION_X - 30, 3);

	_deathText = new TextUI(game, "YOU FAILED", game->getFont("ARIAL12"), 50, CAMERA_RESOLUTION_X / 2, CAMERA_RESOLUTION_Y / 2, { 255,0,0,1 });
	_deathText->setPosition(_deathText->getPosition().getX() - _deathText->getW() / 2, _deathText->getPosition().getY() - _deathText->getH() / 2);
	_deathText->setVisible(false);

	//Añadimos al panel
	addChild(_lifeFrame);
	addChild(_lifeBar);
	addChild(_lifeText);
	addChild(_ammoViewer);
	addChild(_coinsCounter);
	addChild(_weaponryViewer);
	addChild(_dashViewer);
	addChild(_deathText);
}

void PlayerPanel::updateLifeBar(int life, int maxLife)
{
	_lifeBar->updateLifeBar(life, maxLife);

	std::stringstream a, b;

	/*a.fill('0'); a.width(3);*/ a << life << "HP / ";
	b.fill('0'); b.width(3); b << maxLife << "HP";
	a << b.str();

	_lifeText->setText(a.str());
	_lifeText->setScale(0.45f);
	_lifeText->setPosition(_lifeFrame->getX() + _lifeFrame->getW() - _lifeText->getW() - 7, _lifeFrame->getY() + 2 * _lifeFrame->getH() / 3 - 3);
}
