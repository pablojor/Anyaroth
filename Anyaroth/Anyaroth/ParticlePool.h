#pragma once
#include "ObjectPool.h"
#include "Particle.h"
class ParticlePool :
	public ObjectPool<Particle,100>
{
public:
	ParticlePool(Game* game);
	~ParticlePool() {};

	Particle* addNewParticle();
	void stopParticles();
};

