#pragma once
#include "Map.h"

class LevelManager
{
private:
	Game* _game = nullptr;
	Player* _player = nullptr;
	PlayStateHUD* _hud = nullptr;

	GameObject* _level = nullptr;
	Map* _currentMap = nullptr;
	Map* _currentSafeZone = nullptr;
	BulletPool* _enemyBulletPool = nullptr;

	Texture* _tilesetZone1 = nullptr;
	Texture* _tilesetBoss1 = nullptr;
	Texture* _tilesetZone2 = nullptr;

public:
	LevelManager() {}
	LevelManager(Game* game, Player* player, GameObject* level, PlayStateHUD* hud, BulletPool* bulletPool);
	~LevelManager() {}

	enum Level
	{
		Tutorial, Safe1_1, Level1_1, Safe1_2, Level1_2, SafeBoss1, Boss1,
		Safe2_1, Level2_1, Safe2_2, Level2_2, SafeBoss2, Boss2,
		Safe3_1, Level3_1, Safe3_2, Level3_2, SafeBoss3, Boss3, Demo = 20
	};

	void setLevel(int l);
	void changeLevel(int l);
	Map* getCurrentLevel(int l) const;

	inline void resetLevel() { _currentMap->restartLevel(); _enemyBulletPool->stopBullets(); }
};