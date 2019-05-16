#include "SpawnerBoss.h"
#include "MeleeEnemy.h"
#include "MartyrEnemy.h"
#include "DistanceDynamicEnemy.h"
#include "BomberEnemy.h"

bool SpawnerBoss::_spawnTurn = false;
bool SpawnerBoss::_spawnDone = false;

SpawnerBoss::SpawnerBoss(Game* g,Player* player, Vector2D pos, int typeSpawn,BulletPool * pool) :_player(player), _typeSpawn(typeSpawn),_pool(pool), GameObject(g, "Spawn")
{
	_transform = addComponent<TransformComponent>();
	_transform->setPosition(pos.getX(), pos.getY());

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_kinematicBody);
	_body->filterCollisions(OBJECTS, FLOOR);
	_body->getBody()->GetFixtureList()->SetSensor(true);
	_body->getBody()->SetFixedRotation(true);

	if (typeSpawn == 4|| typeSpawn == 5)
	{
		_spawnTime = 1000;
	}
	else if (typeSpawn == 2 || typeSpawn == 3)
	{
		_spawnTime = 500;
	}
}

void SpawnerBoss::update(double deltaTime)
{
	GameObject::update(deltaTime);

	if (_startSpawn)
	{
		switch (_typeSpawn)
		{
		case 5:
			spawnType1(deltaTime);
			break;
		case 4:
			spawnType1(deltaTime);
			break;
		case 3:
			spawnType2(deltaTime);
			break;
		case 2:
			spawnType2(deltaTime);
			break;
		case 1:
			spawnType3(deltaTime);
			break;
		case 0:
			spawnType3(deltaTime);
			break;
		}
	}
}

void SpawnerBoss::spawnType1(double deltaTime)
{
	if (timer >= _spawnTime)
	{
		timer = 0;
		if (_amountSpawned < 4)
		{
			addChild(new MeleeEnemy(_game, _player, _transform->getPosition()));
			_amountSpawned++;
		}
		else
		{
			addChild(new MartyrEnemy(_game, _player, _transform->getPosition()));
			_amountSpawned = 0;
			_startSpawn = false;
		}

	}
	else
		timer += deltaTime;
}

void SpawnerBoss::spawnType2(double deltaTime)
{
	if (timer >= _spawnTime)
	{
		timer = 0;
		if (_amountSpawned < 2)
		{
			addChild(new DistanceDynamicEnemy(_game, _player, _transform->getPosition(),_pool));
			_amountSpawned++;
		}
		else
		{
			_startSpawn = false;
			_amountSpawned = 0;
		}
	}
	else
		timer += deltaTime;
}

void SpawnerBoss::spawnType3(double deltaTime)
{

	if (timer >= _spawnTime)
	{
		timer = 0;
		if (_amountSpawned < 1 && _lastTurn)
		{
			addChild(new BomberEnemy(_game, _player, _transform->getPosition(),_pool));
			_amountSpawned++;
		}
		else
		{
			_startSpawn = false;
			_amountSpawned = 0;
		}
	}
	else
		timer += deltaTime;
}

int SpawnerBoss::aliveEnemies()
{
	int count = 0;
	if (!_startSpawn)
	{
		_spawnDone = false;
		for (auto o : getChildren())
		{
			if (!o->isDead())
				count++;
		}
	}
	else
		count = 100;

	return count;
}