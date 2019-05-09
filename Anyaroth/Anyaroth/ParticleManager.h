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
	priority_queue< ParticleData,vector<ParticleData>,less<ParticleData>> _ParticleQueue;
	
	Game * _game;
	double timer = 0;
public:

	static ParticleManager* GetParticleManager();
	static void deleteManager(); //Only when closing or it can break everything

	inline void setParticlePool(ParticlePool* pull) { _pull = pull; }
	inline int random(int low, int high) const { return low + (rand() % abs(high - low)); }

	void updateManager(const double& deltaTime);
	//inline void setGame(Game* game) { _game = game; }

	void CreateSimpleParticle(Texture * ParticleText,const double textScale, const Vector2D &position, const double &speed, const double & angle, const double & lifeSpan);
	void CreateSimpleParticle(Texture * ParticleText, const double textScale, const Vector2D &position, const double &speed, const double & angle, const double & lifeSpan,const double gravScale);


	void CreateExplosion(Texture * ParticleText, const Vector2D & position, const double &speed, const double & lifeTime, const int & particlesAmount);
	void CreateExplosion(Texture * ParticleText, const Vector2D & position, const double &speed, const double & lifeTime, const int & particlesAmount,const double gravScale);
	void CreateExplosion(Texture * ParticleText, const Vector2D & position, const double &minSpeed,const double &maxSpeed, const double & lifeTime, const int & particlesAmount);
	void CreateExplosion(Texture * ParticleText, const Vector2D & position, const double &minSpeed, const double &maxSpeed, const double & lifeTime, const int & particlesAmount, const double gravScale);

	void CreateSpray(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion,const double &speed, const double & angle, const double & lifeTime, const int & particlesAmount);
	void CreateSpray(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, const double &speed, const double & angle, const double & lifeTime, const int & particlesAmount,const double & gravScale);
	void CreateSpray(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, const double &minSpeed, const double &maxSpeed, const double & angle, const double & lifeTime, const int & particlesAmount);
	void CreateSpray(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, const double &minSpeed, const double &maxSpeed, const double & angle, const double & lifeTime, const int & particlesAmount,const double & gravScale);

	void CreateFountain(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, const double &speed, const double & angle, const double & lifeTime, const int & particlesPerSecond, const double & fountTime);
	void CreateFountain(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, const double &speed, const double & angle, const double & lifeTime, const int & particlesPerSecond, const double & fountTime,const double & gravScale);
	void CreateFountain(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, const double &minSpeed, const double &maxSpeed, const double & angle, const double & lifeTime, const int & particlesPerSecond, const double & fountTime);
	void CreateFountain(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, const double &minSpeed, const double &maxSpeed, const double & angle, const double & lifeTime, const int & particlesPerSecond, const double & fountTime, const double & gravScale);

};


