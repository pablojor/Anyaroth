#pragma once
#include "ParticlePool.h"
#include "Particle.h"
#include "Texture.h"
#include "Vector2D.h"

#include <queue>

class Game;

class ParticleManager
{
private:
	struct ParticleData
	{
		Texture * ParticleText;
		Vector2D  position;
		double speed;
		double angle;
		double lifeSpan;
		double gravScale;
		double timeToSpawn;

		const bool operator <(const ParticleData  other)const
		{
			return (timeToSpawn > other.timeToSpawn);
		}
	};

	static ParticleManager *instance;

	ParticleManager();
	~ParticleManager();

	ParticlePool * _pull;
	priority_queue< ParticleData, vector<ParticleData>, less<ParticleData>> _ParticleQueue;

	Game * _game;
	double timer = 0;

public:
	static ParticleManager* GetParticleManager();
	static void deleteManager(); //Only when closing or it can break everything

	inline void setParticlePool(ParticlePool* pull) { _pull = pull; }
	inline int random(int low, int high) const { return low + (rand() % abs(high - low)); }

	void updateManager(double deltaTime);

	void CreateSimpleParticle(Texture * ParticleText, const double textScale, const Vector2D &position, double speed, double angle, double lifeSpan);
	void CreateSimpleParticle(Texture * ParticleText, const double textScale, const Vector2D &position, double speed, double angle, double lifeSpan, const double gravScale);

	void CreateExplosion(Texture * ParticleText, const Vector2D & position, double speed, double lifeTime, int particlesAmount);
	void CreateExplosion(Texture * ParticleText, const Vector2D & position, double speed, double lifeTime, int particlesAmount, const double gravScale);
	void CreateExplosion(Texture * ParticleText, const Vector2D & position, double minSpeed, double maxSpeed, double lifeTime, int particlesAmount);
	void CreateExplosion(Texture * ParticleText, const Vector2D & position, double minSpeed, double maxSpeed, double lifeTime, int particlesAmount, const double gravScale);

	void CreateSpray(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, double speed, double angle, double lifeTime, int particlesAmount);
	void CreateSpray(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, double speed, double angle, double lifeTime, int particlesAmount, double gravScale);
	void CreateSpray(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, double minSpeed, double maxSpeed, double angle, double lifeTime, int particlesAmount);
	void CreateSpray(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, double minSpeed, double maxSpeed, double angle, double lifeTime, int particlesAmount, double gravScale);

	void CreateFountain(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, double speed, double angle, double lifeTime, int particlesPerSecond, double fountTime);
	void CreateFountain(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, double speed, double angle, double lifeTime, int particlesPerSecond, double fountTime, double gravScale);
	void CreateFountain(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, double minSpeed, double maxSpeed, double angle, double lifeTime, int particlesPerSecond, double fountTime);
	void CreateFountain(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, double minSpeed, double maxSpeed, double angle, double lifeTime, int particlesPerSecond, double fountTime, double gravScale);
};