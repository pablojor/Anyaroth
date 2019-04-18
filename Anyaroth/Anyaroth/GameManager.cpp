#include "GameManager.h"

GameManager GameManager::_instance;
bool GameManager::_initilized = false;


void GameManager::init()
{
	_initilized = true;
}

GameManager * GameManager::getInstance()
{
	if (!_initilized)
		init();

	return &_instance;
}
