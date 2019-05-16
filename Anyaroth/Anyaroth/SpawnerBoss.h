#pragma once
#include "GameObject.h"
#include "DistanceEnemy.h"

class SpawnerBoss : public GameObject
{
private:
	Player * _player;
	TransformComponent* _transform = nullptr;
	BodyComponent* _body = nullptr;
	BulletPool * _pool = nullptr;

	int _typeSpawn, _amountSpawned = 0;

	double _spawnTime = 5000, timer = 0;

	bool _startSpawn = false, _lastTurn = false;

	static bool _spawnTurn, _spawnDone;

public:
	SpawnerBoss(Game* g, Player* player, Vector2D pos, int typeSpawn, BulletPool* pool);
	virtual ~SpawnerBoss() {}

	virtual void update(double deltaTime);

	void spawnType1(double deltaTime);
	void spawnType2(double deltaTime);
	void spawnType3(double deltaTime);

	void spawnEnemy()
	{
		_startSpawn = true;

		if (!_spawnDone)
			_spawnTurn = false;

		if (!_spawnTurn && !_lastTurn)
		{
			if (_typeSpawn == 0 || _typeSpawn == 1)
			{
				_spawnDone = true;
				_spawnTurn = true;
				_lastTurn = true;
			}
		}
		else if (_lastTurn)
		{
			_lastTurn = false;
		}
	}

	int aliveEnemies();
};