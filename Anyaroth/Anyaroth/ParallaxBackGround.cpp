#include "ParallaxBackGround.h"

ParallaxBackGround::~ParallaxBackGround()
{
	for (ParallaxLayer* i : _layers)
		delete i;
}

void ParallaxBackGround::update()
{
	for (ParallaxLayer* i : _layers)
		i->update();
}

void ParallaxBackGround::render() const
{
	for (ParallaxLayer* i : _layers)
		i->render();
}

void ParallaxBackGround::changeDirection(bool normalWay)
{
	for (ParallaxLayer* i : _layers)
		i->changeDir(normalWay);
}
