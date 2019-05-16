#include "ParticleManager.h"
#include "Game.h"

ParticleManager* ParticleManager::instance = nullptr;

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
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

void ParticleManager::updateManager(double deltaTime)
{
	if (!_ParticleQueue.empty())
	{
		ParticleData help = _ParticleQueue.top();
		double scale;
		while (!_ParticleQueue.empty() && help.timeToSpawn < timer)
		{
			scale=  random(5, 15) / 10.0;
			CreateSimpleParticle(help.ParticleText, scale, help.position, help.speed, help.angle, help.lifeSpan, help.gravScale);
			_ParticleQueue.pop();
			if(!_ParticleQueue.empty())
			help = _ParticleQueue.top();
		}
		timer += deltaTime;
	}
}

void ParticleManager::CreateSimpleParticle(Texture * ParticleText, const double textScale, const Vector2D &position, double speed, double angle, double lifeSpan)
{
	Particle * p = _pull->addNewParticle();
	p->init(ParticleText, position, speed, angle, lifeSpan);
	p->getComponent<TransformComponent>()->setScale(textScale);
}

void ParticleManager::CreateSimpleParticle(Texture * ParticleText, const double textScale, const Vector2D & position, double speed, double angle, double lifeSpan, const double gravScale)
{
	Particle * p = _pull->addNewParticle();
	p->init(ParticleText, position, speed, angle, lifeSpan);
	p->setGravScale(gravScale);
	p->getComponent<TransformComponent>()->setScale(textScale);
}

void ParticleManager::CreateExplosion(Texture * ParticleText, const Vector2D & position, double speed, double lifeTime, int particlesAmount)
{
	double angle = 360.0 / particlesAmount;
	double scale;

	for (int i = 0; i < particlesAmount; i++)
	{
		scale = random(5, 15) / 10.0;
		CreateSimpleParticle(ParticleText, scale, position, speed, angle*i, lifeTime);
	}
}

void ParticleManager::CreateExplosion(Texture * ParticleText, const Vector2D & position, double speed, double lifeTime, int particlesAmount, const double gravScale)
{
	double angle = 360 / particlesAmount;
	double scale;

	for (int i = 0; i < particlesAmount; i++)
	{
		scale = random(5, 15) / 10.0;
		CreateSimpleParticle(ParticleText, scale, position, speed, angle*i, lifeTime,gravScale);
	}
}

void ParticleManager::CreateExplosion(Texture * ParticleText, const Vector2D & position, double minSpeed, double maxSpeed, double lifeTime, int particlesAmount)
{
	double angle = 360 / particlesAmount;
	double actualSpeed,scale;

	for (int i = 0; i < particlesAmount; i++)
	{
		scale = random(5, 15) / 10.0;
		actualSpeed = random(minSpeed, maxSpeed);
		CreateSimpleParticle(ParticleText, scale, position, actualSpeed, angle*i, lifeTime);
	}
}

void ParticleManager::CreateExplosion(Texture * ParticleText, const Vector2D & position, double minSpeed, double maxSpeed, double lifeTime, int particlesAmount, const double gravScale)
{
	double angle = 360 / particlesAmount;
	double actualSpeed,scale;

	for (int i = 0; i < particlesAmount; i++)
	{
		scale = random(5, 15) / 10.0;
		actualSpeed = random(minSpeed, maxSpeed);
		CreateSimpleParticle(ParticleText, scale, position, actualSpeed, angle*i, lifeTime,gravScale);
	}
}

void ParticleManager::CreateSpray(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, double speed, double angle, double lifeTime, int particlesAmount)
{
	Vector2D dir = direccion;
	dir.normalize();

	double scale;
	double _angle = angle / particlesAmount, inicialAngle = (atan2(dir.getY(), dir.getX()) * 180 / M_PI) - (particlesAmount / 2) * _angle;

	for (int i = 0; i < particlesAmount; i++)
	{
		scale = random(5, 15) / 10.0;
		CreateSimpleParticle(ParticleText, scale, position, speed, inicialAngle + _angle * i, lifeTime);
	}
}

void ParticleManager::CreateSpray(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, double speed, double angle, double lifeTime, int particlesAmount, double gravScale)
{
	Vector2D dir = direccion;
	dir.normalize();

	double scale;
	double _angle = angle / particlesAmount, inicialAngle = (atan2(dir.getY(), dir.getX()) * 180 / M_PI) - particlesAmount / 2 * _angle;

	for (int i = 0; i < particlesAmount; i++)
	{
		scale = random(5, 15) / 10.0;
		CreateSimpleParticle(ParticleText, scale, position, speed, inicialAngle + _angle * i, lifeTime, gravScale);
	}
}

void ParticleManager::CreateSpray(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, double minSpeed, double maxSpeed, double angle, double lifeTime, int particlesAmount)
{
	Vector2D dir = direccion;
	dir.normalize();

	double _angle = angle / particlesAmount, inicialAngle = (atan2(dir.getY(), dir.getX()) * 180 / M_PI) - particlesAmount / 2 * _angle;
	double actualSpeed ,scale;

	for (int i = 0; i < particlesAmount; i++)
	{
		scale = random(5, 15) / 10.0;
		actualSpeed = random(minSpeed, maxSpeed);
		CreateSimpleParticle(ParticleText, scale, position, actualSpeed, inicialAngle + _angle * i, lifeTime);
	}
}

void ParticleManager::CreateSpray(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, double minSpeed, double maxSpeed, double angle, double lifeTime, int particlesAmount, double gravScale)
{
	Vector2D dir = direccion;
	dir.normalize();

	double _angle = angle / particlesAmount, inicialAngle = (atan2(dir.getY(), dir.getX()) * 180 / M_PI)-particlesAmount/2 * _angle;
	double actualSpeed, scale;

	for (int i = 0; i < particlesAmount; i++)
	{
		scale = random(5, 15) / 10.0;
		actualSpeed = random(minSpeed, maxSpeed);
		CreateSimpleParticle(ParticleText, scale, position, actualSpeed, inicialAngle +_angle*i, lifeTime, gravScale);
	}
}

void ParticleManager::CreateFountain(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, double speed, double angle, double lifeTime, int particlesPerSecond, double fountTime)
{
	Vector2D dir = direccion;
	dir.normalize();

	double _angle = 0, inicialAngle = (atan2(dir.getY(), dir.getX()) * 180 / M_PI) - angle / 2;
	double particleSpawn;
	ParticleData infoP;

	if (particlesPerSecond != 0)
	{
		particleSpawn = 1000 / particlesPerSecond;
		int numbOfParticles = (int)(fountTime / particleSpawn);

		for (int j = 0; j < numbOfParticles; j++)
		{
			infoP.angle = random(0, angle) + inicialAngle;
			infoP.gravScale = 0;
			infoP.lifeSpan = lifeTime;
			infoP.ParticleText = ParticleText;
			infoP.position = position;
			infoP.speed = speed;
			infoP.timeToSpawn = timer + particleSpawn * j;

			_ParticleQueue.push(infoP);
		}
	}
}

void ParticleManager::CreateFountain(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, double speed, double angle, double lifeTime, int particlesPerSecond, double fountTime, double gravScale)
{
	Vector2D dir = direccion;
	dir.normalize();

	double _angle = 0, inicialAngle = (atan2(dir.getY(), dir.getX()) * 180 / M_PI) - angle / 2;
	double particleSpawn;
	ParticleData infoP;

	if (particlesPerSecond != 0)
	{
		particleSpawn = 1000 / particlesPerSecond;
		int numbOfParticles = (int)(fountTime / particleSpawn);

		for (int j = 0; j < numbOfParticles; j++)
		{
			infoP.angle = random(0, angle) + inicialAngle;
			infoP.gravScale = gravScale;
			infoP.lifeSpan = lifeTime;
			infoP.ParticleText = ParticleText;
			infoP.position = position;
			infoP.speed = speed;
			infoP.timeToSpawn = timer + particleSpawn * j;

			_ParticleQueue.push(infoP);
		}
	}
}

void ParticleManager::CreateFountain(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, double minSpeed, double maxSpeed, double angle, double lifeTime, int particlesPerSecond, double fountTime)
{
	Vector2D dir = direccion;
	dir.normalize();

	double _angle = 0, inicialAngle = (atan2(dir.getY(), dir.getX()) * 180 / M_PI) - angle / 2;
	double particleSpawn;
	ParticleData infoP;
	double actualSpeed;

	if (particlesPerSecond != 0)
	{
		particleSpawn = 1000 / particlesPerSecond;
		int numbOfParticles = (int)(fountTime / particleSpawn);

		for (int j = 0; j < numbOfParticles; j++)
		{
			actualSpeed = random(minSpeed, maxSpeed);
			infoP.angle = random(0, angle) + inicialAngle;
			infoP.gravScale = 0;
			infoP.lifeSpan = lifeTime;
			infoP.ParticleText = ParticleText;
			infoP.position = position;
			infoP.speed = actualSpeed;
			infoP.timeToSpawn = timer + particleSpawn * j;

			_ParticleQueue.push(infoP);
		}
	}
}

void ParticleManager::CreateFountain(Texture * ParticleText, const Vector2D & position, const Vector2D & direccion, double minSpeed, double maxSpeed, double angle, double lifeTime, int particlesPerSecond, double fountTime, double gravScale)
{
	Vector2D dir = direccion;
	dir.normalize();

	double _angle = 0, inicialAngle = (atan2(dir.getY(), dir.getX()) * 180 / M_PI) - angle / 2;
	double particleSpawn;
	ParticleData infoP;
	double actualSpeed;

	if (particlesPerSecond != 0)
	{
		particleSpawn = 1000 / particlesPerSecond;
		int numbOfParticles = (int)(fountTime / particleSpawn);

		for (int j = 0; j < numbOfParticles; j++)
		{
			actualSpeed = random(minSpeed, maxSpeed);
			infoP.angle = random(0, angle) + inicialAngle;
			infoP.gravScale = gravScale;
			infoP.lifeSpan = lifeTime;
			infoP.ParticleText = ParticleText;
			infoP.position = position;
			infoP.speed = actualSpeed;
			infoP.timeToSpawn = timer + particleSpawn * j;

			_ParticleQueue.push(infoP);
		}
	}
}