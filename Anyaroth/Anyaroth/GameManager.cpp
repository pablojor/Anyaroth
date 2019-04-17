#include "GameManager.h"

std::unique_ptr<GameManager> GameManager::_instance = nullptr;

void GameManager::init()
{
	if (_instance.get() == nullptr) {
		_instance.reset(new GameManager());
	}
}

GameManager * GameManager::getInstance()
{
	if (_instance.get() == nullptr) {
		_instance.reset(new GameManager());
	}
	return _instance.get();
}
