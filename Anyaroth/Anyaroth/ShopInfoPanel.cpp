#include "ShopInfoPanel.h"
#include "Game.h"


ShopInfoPanel::ShopInfoPanel(Game* game, int xPos, int yPos) : PanelUI(game)
{
	_backImage = new ImageUI(game, game->getTexture("InfoPanel"), xPos, yPos);

	_nameText = new TextUI(game, "ExampleName", game->getFont("ARIAL12"), 12);
	_nameText->setPosition((xPos + _backImage->getW() / 2) - _nameText->getW() / 2, yPos + 4);

	_buyButton = new ButtonUI(game, game->getTexture("BuyButton"), nullptr, { 0,1,2,1 });
	_buyButton->setPosition(xPos + 1, yPos + _backImage->getH() - _buyButton->getH() - 1);

	int hRest = _backImage->getH() - _nameText->getH() - _buyButton->getH();
	int hOffset = 3;

	_damageImage = new ImageUI(game, game->getTexture("InfoIcon"), _buyButton->getX(), _nameText->getY() + _nameText->getH() + hOffset);
	_damageText = new TextUI(game, "damage", game->getFont("ARIAL12"), 12, _damageImage->getX() + _damageImage->getW() + 2, _damageImage->getY() + 1);

	_cadenceImage = new ImageUI(game, game->getTexture("InfoIcon"), _buyButton->getX(), _damageImage->getY() + _damageImage->getH() + hOffset);
	_cadenceText = new TextUI(game, "cadence", game->getFont("ARIAL12"), 12, _cadenceImage->getX() + _cadenceImage->getW() + 2, _cadenceImage->getY() + 1);

	_distanceImage = new ImageUI(game, game->getTexture("InfoIcon"), _buyButton->getX(), _cadenceImage->getY() + _cadenceImage->getH() + hOffset);
	_distanceText = new TextUI(game, "distance", game->getFont("ARIAL12"), 12, _distanceImage->getX() + _distanceImage->getW() + 2, _distanceImage->getY() + 1);

	/*_priceImage = nullptr;
	_priceText = nullptr;*/

	addChild(_backImage);
	addChild(_nameText);
	addChild(_buyButton);
	addChild(_damageImage);
	addChild(_damageText);
	addChild(_cadenceImage);
	addChild(_cadenceText);
	addChild(_distanceImage);
	addChild(_distanceText);
}

ShopInfoPanel::~ShopInfoPanel()
{
}
