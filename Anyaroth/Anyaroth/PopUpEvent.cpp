#include "PopUpEvent.h"
#include "GameManager.h"
#include "LevelManager.h"

void PopUpEvent::update(double time)
{
	if (_popUpPanel->isFinished())
		_finished = true;
}

void PopUpEvent::play()
{
	if (GameManager::getInstance()->getCurrentLevel() == LevelManager::Boss1)
	{
		_popUpPanel->addMessage({ "Notification:","You have acquired Spenta's sword and part of his power. Your health increases significantly." });
		_popUpPanel->open();
	}
	else if (GameManager::getInstance()->getCurrentLevel() == LevelManager::Boss2)
	{
		_popUpPanel->addMessage({ "Notification:","You have acquired Azura's poleaxe and part of his power. Your health increases significantly." });
		_popUpPanel->open();
	}
}