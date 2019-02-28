#include "PlayStateHUD.h"


PlayStateHUD::PlayStateHUD(Game * g)
{
	//Vida
	_lifeBar = ImageUI(g, g->getTexture("Ammo"));
	_lifeBar.setPosition(20, 20);
	addUIElement(&_lifeBar);
	//Ammo
	_ammo = TextUI(g, "AMMO");
	addUIElement(&_ammo);

}

PlayStateHUD::~PlayStateHUD()
{

}
