#include "CoinsCounter.h"
#include "Game.h"


CoinsCounter::CoinsCounter(Game* game, int xPos, int yPos) : PanelUI(game)
{
	_coinText = new TextUI(game, to_string(0), game->getFont("ARIAL12"), 12, xPos, yPos + 4, { 255, 255, 255, 255 });
	_coinImage = new ImageUI(game, game->getTexture("CoinIcon"), xPos + _coinText->getW() + 3, yPos);

	addChild(_coinText);
	addChild(_coinImage);
}

void CoinsCounter::updateCoinsCounter(int cant)
{
	int x = _coinText->getX();
	int w = _coinText->getW();
	_coinText->setText(to_string(cant));
	_coinText->setPosition(x - (_coinText->getW() - w), _coinText->getY());
}