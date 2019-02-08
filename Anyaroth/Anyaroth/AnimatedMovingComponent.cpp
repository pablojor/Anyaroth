#include "AnimatedMovingComponent.h"


void AnimatedMovingComponent::update() 
{
	MovingComponent::update();
	_ac->updateFrame();

}
