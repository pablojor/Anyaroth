#pragma once
#include "GameState.h"
#include "DebugDraw.h"
#include "LevelManager.h"
#include "CollisionManager.h"
#include "ParallaxBackGround.h"
#include "Player.h"
#include "BulletPool.h"
#include "Cursor.h"
#include "PlayStateHUD.h"
#include "Shop.h"

class CutScene;

class PlayState : public GameState
{
private:
	Player* _player = nullptr;
	BulletPool* _playerBulletPool = nullptr;
	Cursor* _cursor = nullptr;
	PlayStateHUD* _hud = nullptr;

	CutScene* _cutScene = nullptr;

	LevelManager _levelManager;
	CollisionManager _colManager;
	DebugDraw _debugger;

	ParallaxBackGround* _parallaxZone1 = nullptr;

	int _currentLevel;

public:
	PlayState(Game* g);
	virtual ~PlayState();

	virtual void render() const;
	virtual void update(const double& deltaTime);
	virtual bool handleEvent(const SDL_Event& event);

	inline int getCurrentLevel() const { return _currentLevel; }

	inline virtual void addCutScene(CutScene* cutScene) { _cutScene = cutScene; };
};