#pragma once
#include "Map.h"
#include "Camera.h"

class LevelManager
{
private:
	Game* _game = nullptr;
	Camera* _camera = nullptr;

	Player* _player = nullptr;
	GameObject* _level = nullptr;
	BulletPool* _enemyBulletPool = nullptr;
  
	Map* _currentMap = nullptr;
	Map* _currentSafeZone = nullptr;
  
	Texture* _tilesetZone1 = nullptr;
	Texture* _tilesetZone2 = nullptr;
	Texture* _tilesetBoss1 = nullptr;
	Texture* _tilesetBoss2 = nullptr;
	Texture* _tilesetBoss3 = nullptr;

	void setControlsBackground();
	void setParallaxZone1();
	void setBackgroundBoss1();

public:
	LevelManager() {}
	LevelManager(Game* game, Player* player, GameObject* level, BulletPool* bulletPool);
	~LevelManager() {}

	enum Level
	{
		Tutorial, Safe1_1, Level1_1, Safe1_2, Level1_2, SafeBoss1, Boss1,
		Safe2_1, Level2_1, Safe2_2, Level2_2, SafeBoss2, Boss2,
		Safe3_1, Level3_1, Safe3_2, Level3_2, SafeBoss3, Boss3,
		SafeDemo = 51, LevelDemo = 52, SafeBossDemo = 53, BossDemo = 54
	};

	void setLevel(int l);
	void changeLevel(int l);
	Map* getCurrentLevel(int l) const;

	void resetLevel();
};