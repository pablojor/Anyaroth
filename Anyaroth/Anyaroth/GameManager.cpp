#include "GameManager.h"
#include "LevelManager.h"

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

void GameManager::nextLevel()
{
	if (_currentLevel < LevelManager::Boss3 || _currentLevel < LevelManager::BossDemo)
		_currentLevel++;
}

void GameManager::previousLevel()
{
	if (_currentLevel > LevelManager::Tutorial || _currentLevel > LevelManager::SafeDemo)
		_currentLevel--;
}