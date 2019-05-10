#include "LaserHandler.h"
#include "Game.h"

LaserHandler::LaserHandler(Game* g, Texture* container, Texture* laser, Player* player, int numLasers, int span, Vector2D pos) : _numLasers(numLasers), GameObject(g)
{
	int spaceBetween = (span - pos.getX()) / numLasers;

	for (int i = 0; i < numLasers; i++)
	{
		LaserContainer* temp = new LaserContainer(g, Vector2D(pos.getX() + i * spaceBetween, pos.getY()), container, laser, player);

		_lasers.push_back(temp);
		addChild(temp);
	}
}

void LaserHandler::update(const double& deltaTime)
{
	if (_active)
	{
		GameObject::update(deltaTime);
		if (isShooting)
		{
			if (shootStareted)
			{
				if (timeToshot > timeToEnd)
				{
					isShooting = false;
					shootStareted = false;
					timeToshot = 0;
					Stop();
				}
				else
					timeToshot += deltaTime;
			}
			else
			{
				Shoot();
				shootStareted = true;
			}		
		}
		else
		{
			if (timeToshot > timeBetweenShot)
			{
				isShooting = true;
				timeToshot = 0;
			}
			else
			{
				if ((timeBetweenShot - timeToshot) <= 1000)
				{
					for (auto l : _lasers)
					{
						l->setActive(true);
						l->Warning();
					}
				}
				timeToshot += deltaTime;
			}
		}
	}
}

void LaserHandler::Shoot()
{
	_lasers[0]->Shoot(_game->random(60, 100));

	for (int i = 1; i < _numLasers - 1; i++)
	{
		_lasers[i]->Shoot(_game->random(60, 120));
	}

	_lasers[_numLasers - 1]->Shoot(_game->random(80, 120));
}
void LaserHandler::Stop()
{
	for (LaserContainer* o : _lasers)
	{
		o->Stop();
	}
}