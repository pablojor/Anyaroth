#include "PlayStateHUD.h"
#include "Game.h"

PlayStateHUD::PlayStateHUD(Game * g)
{
	//Panel del jugador
	_playerPanel = new PlayerPanel(g);
	//Panel del Boss
	//_bossPanel = new BossPanel(g);


	//Panel de dialogos
	_dialoguePanel = new DialoguePanel(g);

	//A�adir a elementos
	addUIElement(_playerPanel);
	//addUIElement(_bossPanel);
	addUIElement(_dialoguePanel);
}