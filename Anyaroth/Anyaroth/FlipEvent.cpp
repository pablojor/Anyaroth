#include "FlipEvent.h"



FlipEvent::FlipEvent(Player* player) : Event(), _player(player)
{
}

void FlipEvent::play()
{
	if (!_player->getComponent<CustomAnimatedSpriteComponent>()->isFlipped())
		_player->getComponent<CustomAnimatedSpriteComponent>()->flip();
	else
		_player->getComponent<CustomAnimatedSpriteComponent>()->unFlip();

	_finished = true;
}
