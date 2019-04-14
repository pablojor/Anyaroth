#include "WeaponryViewer.h"
#include "Game.h"

WeaponryViewer::WeaponryViewer(Game* game, int xPos, int yPos) : PanelUI(game)
{
	_marco = new ImageUI(game, game->getTexture("CurrentWeapon"));

	int marcoPosX = xPos,
		marcoPosY = yPos - _marco->getH() - 3;

	_marco->setPosition(marcoPosX, marcoPosY);

	_currentWeapon = new ImageUI(game, game->getTexture("Weapon1"));
	_currentWeapon->setPosition(marcoPosX + (_marco->getW() - _currentWeapon->getW()) / 2,
								marcoPosY + (_marco->getH() - _currentWeapon->getH()) / 2);

	_otherWeapon = new ImageUI(game, game->getTexture("Weapon2"));

	addChild(_marco);
	addChild(_currentWeapon);
}

void WeaponryViewer::updateWeaponryViewer(Texture* iconTex)
{
	/*Texture* aux = _currentWeapon->getImage();
	_currentWeapon->setImage(_otherWeapon->getImage());
	_otherWeapon->setImage(aux);*/

	_currentWeapon->setImage(iconTex);
}