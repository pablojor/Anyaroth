#pragma once
#include "ParticlePull.h"
#include "Particle.h"
#include "Texture.h"
#include "Vector2D.h"

class Game;

class ParticleManager
{
private:
	static ParticleManager *instance;
	ParticleManager();
	~ParticleManager();

	ParticlePull * _pull;
	Game * _game;
public:

	static ParticleManager* GetParticleManager();
	static void deleteManager(); //Only when closing or it can break everything

	inline void setParticlePull(ParticlePull* pull) { _pull = pull; }
	//inline void setGame(Game* game) { _game = game; }

	void CreateSimpleParticle(Texture * ParticleText, const Vector2D &position, const double &speed, const double & angle, const double & lifeSpan);
};


