#pragma once
#include "GameState.h"
#include "DebugDraw.h"
#include "LevelManager.h"
#include "CollisionManager.h"
#include "ParticleManager.h"
#include "ParallaxBackGround.h"
#include "Player.h"
#include "BulletPool.h"
#include "ParticlePull.h"
#include "PlayStateHUD.h"
#include "Cursor.h"

class PlayState : public GameState
{
private:
	Player* _player = nullptr;
	BulletPool* _playerBulletPool = nullptr;
	ParticlePull * _particles = nullptr;

	GameObject* _level = nullptr;
	Cursor* _cursor = nullptr;

	LevelManager _levelManager;
	CollisionManager _colManager;
	ParticleManager * _particleManager = nullptr;
	DebugDraw _debugger;

	ParallaxBackGround* _parallaxZone1 = nullptr;

public:
	PlayState(Game* g);
	virtual ~PlayState();

	virtual void render() const;
	virtual void update(const double& deltaTime);
	virtual bool handleEvent(const SDL_Event& event);

	void saveGame();
	void loadGame();
};