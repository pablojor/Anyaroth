#include "LaserHandler.h"
#include "Game.h"

LaserHandler::LaserHandler(Game* g, Texture* container, Texture* laser, Player* player, int numLasers) : GameObject(g)
{
	int pos1 = 40;
	int spaceBetween = (400 - pos1) / numLasers;

	for (int i = 0; i < numLasers; i++)
	{
		LaserContainer* temp = new LaserContainer(g, Vector2D(pos1 + i * spaceBetween, 200), container, laser, player);

		_lasers.push_back(temp);
		addChild(temp);
	}
}

void LaserHandler::update(const double& deltaTime)
{
	if (_active)
	{
		if (timeBetweenShot > timeBetweenShot)
		{
			Shoot(_game->random(220, 340));
		}
		else
			timeBetweenShot += deltaTime;
	}
}

void LaserHandler::Shoot(double angle)
{
	for (LaserContainer* o : _lasers)
	{
		o->Shoot(angle);
	}
}
void LaserHandler::Stop()
{
	for (LaserContainer* o : _lasers)
	{
		o->Stop();
	}
}