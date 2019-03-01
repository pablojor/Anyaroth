#include "WeaponryViewer.h"
#include "Game.h"



WeaponryViewer::WeaponryViewer(Game* game, int xPos, int yPos) : PanelUI(game)
{
	_currentWeapon = new ImageUI(game, game->getTexture("example1"), xPos, yPos);
	_secondWeapon = new ImageUI(game, game->getTexture("body"), xPos, yPos + 25);
	_meleeWeapon = new ImageUI(game, game->getTexture("CoinIcon"), xPos, yPos + 50);

	addChild(_currentWeapon);
	addChild(_secondWeapon);
	addChild(_meleeWeapon);
}


void WeaponryViewer::updateWeaponryViewer()
{
	Texture* aux = _currentWeapon->getImage();
	_currentWeapon->setImage(_secondWeapon->getImage());
	_secondWeapon->setImage(aux);
}
