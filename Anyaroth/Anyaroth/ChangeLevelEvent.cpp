#include "ChangeLevelEvent.h"

void ChangeLevelEvent::play()
{
	_player->setChangeLevel(true);
	_finished = true;
}