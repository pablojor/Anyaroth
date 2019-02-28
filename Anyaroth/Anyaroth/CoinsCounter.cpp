#include "CoinsCounter.h"
#include "Game.h"


CoinsCounter::CoinsCounter(Game* game) : PanelUI(game)
{
	_coinImage = new ImageUI(game, game->getTexture("CoinIcon"));
	_coinText = new TextUI(game, to_string(_coinCount), game->getFont("ARIAL12"), 12, { 255, 255, 255, 255 });

	addChild(_coinImage);
	addChild(_coinText);

	_coinImage->setPosition(GAME_RESOLUTION_X - _coinImage->getW(), 0);
	_coinText->setPosition(_coinImage->getX() - _coinImage->getW(), ((_coinImage->getY() + _coinImage->getH()) / 2) - (_coinText->getH() / 2) + 1);
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

