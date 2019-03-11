#include "WeaponryViewer.h"
#include "Game.h"

WeaponryViewer::WeaponryViewer(Game* game, int xPos, int yPos) : PanelUI(game)
{
	_currentWeapon = new ImageUI(game, game->getTexture("WeaponFrame"), xPos, yPos);
	_otherWeapon = new ImageUI(game, game->getTexture("WeaponFrame"), xPos, yPos + _currentWeapon->getH() + 1);
	_meleeWeapon = new ImageUI(game, game->getTexture("WeaponFrame"), xPos, _otherWeapon->getY() + _otherWeapon->getH() + 1);

	addChild(_meleeWeapon);
	addChild(_otherWeapon);
	addChild(_currentWeapon);
}

void WeaponryViewer::updateWeaponryViewer()
{
	Texture* aux = _currentWeapon->getImage();
	_currentWeapon->setImage(_otherWeapon->getImage());
	_otherWeapon->setImage(aux);
}