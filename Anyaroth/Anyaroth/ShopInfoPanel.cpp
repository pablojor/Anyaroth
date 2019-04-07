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
	_damageIcon = new ImageUI(game, game->getTexture("CadenceIcon"));
	_damageIcon->setPosition(_frame->getX() + 7, _frame->getY() + 19);

	_damageBar = new ImageUI(game, game->getTexture("PropertiesBar"));
	_damageBar->setPosition(_damageIcon->getX() + _damageIcon->getW() + 5, 
							_damageIcon->getY() + _damageIcon->getH() / 2 - _damageBar->getH() / 2);

	//--Cadence
	_cadenceIcon = new ImageUI(game, game->getTexture("CadenceIcon"));
	_cadenceIcon->setPosition(_damageIcon->getX(),
								_damageIcon->getY() + _damageIcon->getH());

	_cadenceBar = new ImageUI(game, game->getTexture("PropertiesBar"));
	_cadenceBar->setPosition(_damageBar->getX(),
								_cadenceIcon->getY() + _cadenceIcon->getH() / 2 - _cadenceBar->getH() / 2);

	//--Distance
	_ammoIcon = new ImageUI(game, game->getTexture("CadenceIcon"));
	_ammoIcon->setPosition(_cadenceIcon->getX(),
								_cadenceIcon->getY() + _cadenceIcon->getH());

	_ammoBar = new ImageUI(game, game->getTexture("PropertiesBar"));
	_ammoBar->setPosition(_cadenceBar->getX(),
								_ammoIcon->getY() + _ammoIcon->getH() / 2 - _ammoBar->getH() / 2);

	//--Precio
	_priceText = new TextUI(game, "0000", game->getFont("ARIAL12"), 12);
	_priceIcon = new ImageUI(game, game->getTexture("CoinIcon"));

	_priceText->setPosition(_frame->getX() + _frame->getW() / 2 - (_priceText->getW() + _priceIcon->getW() + 2) / 2,
							_ammoBar->getY() + _ammoBar->getH() + 6);
	_priceIcon->setPosition(_priceText->getX() + _priceText->getW() + 2,
							_priceText->getY() + _priceText->getH() / 2 - _priceIcon->getH() / 2);

	addChild(_damageIcon);
	addChild(_damageBar);
	addChild(_cadenceIcon);
	addChild(_cadenceBar);
	addChild(_ammoIcon);
	addChild(_ammoBar);
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

void ShopInfoPanel::setCadence(int cadence)
{

}

void ShopInfoPanel::setPrice(int price)
{
	_priceText->setText(to_string(price));
}
