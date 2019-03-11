#include "ParallaxBackGround.h"


ParallaxBackGround::~ParallaxBackGround()
{
	for (ParallaxLayer* i : _layers)
		delete i;
}

void ParallaxBackGround::update(double time)
{
	for (ParallaxLayer* i : _layers)
		i->update(time);
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

bool ParallaxBackGround::checkCameraStatus(pair<bool, int> status)
{
	if (status.first)
	{
		status.second == 1 ? changeDirection(true) : changeDirection(false);
		return true;
	}
	return false;
}