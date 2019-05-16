#include "PlayMusicEvent.h"

void PlayMusicEvent::play()
{
	_game->getSoundManager()->playMusic(_music);
	_finished = true;
}