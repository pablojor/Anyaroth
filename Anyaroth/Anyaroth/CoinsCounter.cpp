#include "CoinsCounter.h"
#include "Game.h"


CoinsCounter::CoinsCounter(Game* game, int xPos, int yPos) : PanelUI(game)
{
	_coinText = new TextUI(game, to_string(_coinCount), game->getFont("ARIAL12"), 12, xPos, yPos + 1, { 255, 255, 255, 255 });
	_coinImage = new ImageUI(game, game->getTexture("CoinIcon"), xPos + _coinText->getW(), yPos - 1);

	addChild(_coinText);
	addChild(_coinImage);
}

void CoinsCounter::update()
{
	_coinCount++;
	updateAspect();
}

void CoinsCounter::updateAspect()
{
	int x = _coinText->getX();
	int w = _coinText->getW();
	_coinText->setText(to_string(_coinCount));
	_coinText->setPosition(x - (_coinText->getW() - w), _coinText->getY());
}

