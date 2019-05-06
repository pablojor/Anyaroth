#include "PlayStateHUD.h"
#include "Game.h"


PlayStateHUD::PlayStateHUD(Game * g)
{
	//Panel del jugador
	_playerPanel = new PlayerPanel(g);

	//Panel del Boss
	_bossPanel = new BossPanel(g);

	//Panel del Boss
	_boss3Panel = new Boss3Panel(g);

	//Panel de Tienda
	_shopMenu = new ShopMenu(g);

	//Panel de dialogos
	_dialoguePanel = new DialoguePanel(g);

	//Barra de vida de enemigos pequeños
	_enemyLifePanel = new EnemyLifePanel(g);

	//Anyadir a elementos
	addUIElement(_enemyLifePanel);
	addUIElement(_playerPanel);
	addUIElement(_bossPanel);
	addUIElement(_boss3Panel);
	addUIElement(_shopMenu);
	addUIElement(_dialoguePanel);

	//Asignaciones
	_shopMenu->setDialoguePanel(_dialoguePanel);
}

