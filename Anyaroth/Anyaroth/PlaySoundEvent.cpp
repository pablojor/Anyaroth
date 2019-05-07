#include "PlaySoundEvent.h"

void PlaySoundEvent::play()
{
	_game->getSoundManager()->playSFX(_sound);
	_finished = true;
}