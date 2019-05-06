#include "ParticlePool.h"
#include "Game.h"


ParticlePool::ParticlePool(Game* game) : ObjectPool<Particle, 100>(game) {}




Particle * ParticlePool::addNewParticle()
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

void ParticlePool::stopParticles()
{
	for (auto b : _objects)
	{
		b->reset();
		b->setActive(false);
	}
}
