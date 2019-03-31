#include "ShopInfoPanel.h"
#include "Game.h"


ShopInfoPanel::ShopInfoPanel(Game* game, int xPos, int yPos) : PanelUI(game)
{
	//----MARCO----//

	_frame = new ImageUI(game, game->getTexture("InfoPanel"), xPos, yPos);
	_frame->setSize(_frame->getW() * 1.5, _frame->getH() * 1.25);

	addChild(_frame);

	//----INFORMACION----//

		// Nombre
	_nameText = new TextUI(game, "ExampleName", game->getFont("ARIAL12"), 12);
	_nameText->setPosition((xPos + _frame->getW() / 2) - _nameText->getW() / 2, yPos + margin);
	addChild(_nameText);

		// Propiedades
	//--Damage
	_damageIcon = new ImageUI(game, game->getTexture("InfoIcon"));
	_damageIcon->setPosition(xPos + margin, 
							_nameText->getY() + _nameText->getH() + margin);

	_damageBar = new ImageUI(game, game->getTexture("LifeBarMask"));
	_damageBar->setSize(_damageBar->getW() * 0.5, _damageBar->getH() * 0.5); //PROVISIONAL
	_damageBar->setPosition(_damageIcon->getX() + _damageIcon->getW() + margin, 
							_damageIcon->getY() + _damageIcon->getH() / 2 - _damageBar->getH() / 2);

	//--Cadence
	_cadenceIcon = new ImageUI(game, game->getTexture("InfoIcon"));
	_cadenceIcon->setPosition(_damageIcon->getX(),
								_damageIcon->getY() + _damageIcon->getH() + margin);

	_cadenceBar = new ImageUI(game, game->getTexture("LifeBarMask"));
	_cadenceBar->setSize(_cadenceBar->getW() * 0.5, _cadenceBar->getH() * 0.5); //PROVISIONAL
	_cadenceBar->setPosition(_damageBar->getX(),
								_cadenceIcon->getY() + _cadenceIcon->getH() / 2 - _cadenceBar->getH() / 2);

	//--Distance
	_distanceIcon = new ImageUI(game, game->getTexture("InfoIcon"));
	_distanceIcon->setPosition(_cadenceIcon->getX(),
								_cadenceIcon->getY() + _cadenceIcon->getH() + margin);

	_distanceBar = new ImageUI(game, game->getTexture("LifeBarMask"));
	_distanceBar->setSize(_distanceBar->getW() * 0.5, _distanceBar->getH() * 0.5); //PROVISIONAL
	_distanceBar->setPosition(_cadenceBar->getX(),
								_distanceIcon->getY() + _distanceIcon->getH() / 2 - _distanceBar->getH() / 2);

	//--Precio
	_priceText = new TextUI(game, "0000", game->getFont("ARIAL12"), 12);
	_priceIcon = new ImageUI(game, game->getTexture("CoinIcon"));

	_priceText->setPosition(_frame->getX() + _frame->getW() / 2 - (_priceText->getW() + _priceIcon->getW() + 2) / 2,
							_distanceIcon->getY() + _distanceIcon->getH() + margin);
	_priceIcon->setPosition(_priceText->getX() + _priceText->getW() + 2,
							_priceText->getY() + _priceText->getH() / 2 - _priceIcon->getH() / 2);

	addChild(_damageIcon);
	addChild(_damageBar);
	addChild(_cadenceIcon);
	addChild(_cadenceBar);
	addChild(_distanceIcon);
	addChild(_distanceBar);
	addChild(_priceText);
	addChild(_priceIcon);
}

void ShopInfoPanel::setName(string name)
{
	_nameText->setText(name);
	_nameText->setPosition((_frame->getX() + _frame->getW() / 2) - _nameText->getW() / 2, _frame->getY() + margin);
}

void ShopInfoPanel::setDamage(int damage)
{

}

void ShopInfoPanel::setDistance(int distance)
{

}

void ShopInfoPanel::setCadence(int price)
{

}
