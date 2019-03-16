#pragma once
#include "GameComponent.h"
#include "Map.h"
#include "ParallaxBackGround.h"
#include <list>

class LevelManager : public GameComponent
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
	LevelManager(Game* g, PlayState* playstate, Player* player, list<GameObject*>& list);
	~LevelManager();

	void setLevel(int zone, int level);
	void changeLevel(int zone, int level);
	inline Map* getCurrentMap() const { return _currentMap; }
};