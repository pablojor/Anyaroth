#pragma once
#include "ObjectPool.h"
#include "Particle.h"
class ParticlePull :
	public ObjectPool<Particle,100>
{
public:
	ParticlePull(Game* game);
	~ParticlePull() {};

	Particle* addNewParticle();
	void stopParticles();
};

