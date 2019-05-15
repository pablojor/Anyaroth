#include "ChangeLevelEvent.h"
#include "GameManager.h"

void ChangeLevelEvent::play()
{
	GameManager::getInstance()->setChangeLevel(true);
	_finished = true;
}