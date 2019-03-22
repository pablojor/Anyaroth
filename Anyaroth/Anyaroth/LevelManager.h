#pragma once
#include "Map.h"
#include "ParallaxBackGround.h"
#include <list>

class LevelManager
{
private:
	Game* _game = nullptr;
	PlayState* _playState = nullptr;
	Player* _player = nullptr;

	Camera* _mainCamera = nullptr;
	Texture* _tilesetZone1 = nullptr;
	ParallaxBackGround* _parallaxZone1 = nullptr;

	Map* _currentMap = nullptr;

	list<GameObject*>* _stages = nullptr;

public:
	LevelManager() {}
	LevelManager(Game* game, PlayState* playstate);
	~LevelManager() {}

	void setLevel(int zone, int level);
	void changeLevel(int zone, int level);
	inline void resetLevel() { _currentMap->restartLevel(); }

	inline Map* getCurrentMap() const { return _currentMap; }
};