#include "AmmoViewer.h"
#include "Game.h"
#include <sstream>

AmmoViewer::AmmoViewer(Game* game, int xPos, int yPos) : PanelUI(game)
{
	_clipText = new TextUI(game, "00", game->getFont("ARIAL12"), 12, xPos, yPos, { 255, 255, 255, 255 });
	_magazineText = new TextUI(game," / 000", game->getFont("ARIAL12"), 12, xPos + _clipText->getW(), yPos, { 255, 255, 255, 255 });

	_ammoImage = new ImageUI(game, game->getTexture("AmmoIcon"), xPos, yPos + _clipText->getH() + 2);

	addChild(_clipText);
	addChild(_magazineText);
	addChild(_ammoImage);
}

void AmmoViewer::updateAmmoViewer(int ammoClip, int ammoMagazine)
{
	int x = _clipText->getX();
	int w = _clipText->getW();

	std::stringstream a; 

	a.fill('0'); a.width(2); a << ammoClip;
	_clipText->setText(a.str());

	a.str(""); a.fill('0'); a.width(3); a << ammoMagazine;
	_magazineText->setText(" / " + a.str());

	_clipText->setPosition(x - (_clipText->getW() - w), _clipText->getY());
}