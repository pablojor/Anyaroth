#include "ParticlePull.h"
#include "Game.h"


ParticlePull::ParticlePull(Game* game) : ObjectPool<Particle, 100>(game) {}




Particle * ParticlePull::addNewParticle()
{

	Particle* b = getUnusedObject();
	if (b == nullptr)
	{
		b = new Particle(getGame());

		_objects.push_back(b);
		b->setWorld(getWorld());
	}
	return b;
}

void ParticlePull::stopParticles()
{
	for (auto b : _objects)
	{
		b->reset();
		b->setActive(false);
	}
}
