#include "AmmoViewer.h"
#include "Game.h"


AmmoViewer::AmmoViewer(Game* game, int xPos, int yPos) : PanelUI(game)
{
	_clipText = new TextUI(game, "00", game->getFont("ARIAL12"), 12, xPos, yPos, { 255, 255, 255, 255 });
	_magazineText = new TextUI(game," / 000", game->getFont("ARIAL12"), 12, xPos + _clipText->getW(), yPos, { 255, 255, 255, 255 });

	addChild(_clipText);
	addChild(_magazineText);
}


void AmmoViewer::updateAmmoViewer(const int& ammoClip, const int& ammoMagazine)
{
	int x = _clipText->getX();
	int w = _clipText->getW();

	_clipText->setText(to_string(ammoClip));
	_magazineText->setText(" / " + to_string(ammoMagazine));

	_clipText->setPosition(x - (_clipText->getW() - w), _clipText->getY());
}

