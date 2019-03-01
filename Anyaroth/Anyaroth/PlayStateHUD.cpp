#include "PlayStateHUD.h"
#include "Game.h"


PlayStateHUD::PlayStateHUD(Game * g)
{
	//Panel del jugador
	_playerPanel = new PlayerPanel(g);
	//Panel del Boss
	//_bossPanel = new BossPanel(g);

	//Añadir a elementos
	addUIElement(_playerPanel);
	//addUIElement(_bossPanel);
}

