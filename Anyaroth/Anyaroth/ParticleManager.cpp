#include "ParticleManager.h"
#include "Game.h"

ParticleManager* ParticleManager::instance = nullptr;

ParticleManager::ParticleManager()
{
	
}


ParticleManager * ParticleManager::GetParticleManager()
{
	if (instance == nullptr)
	{
		instance = new ParticleManager();
	}
	return instance;
}

void ParticleManager::deleteManager()
{
	delete(instance);
	instance = nullptr;
}

void ParticleManager::CreateSimpleParticle(Texture * ParticleText, const Vector2D &position, const double &speed, const double & angle, const double & lifeSpan)
{
	Particle * p = _pull->addNewParticle();
	p->init(ParticleText, position, speed, angle, lifeSpan);
	
}

ParticleManager::~ParticleManager()
{
}
