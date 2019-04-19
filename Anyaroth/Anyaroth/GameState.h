#pragma once
#include <list>
#include <vector>
#include "GameObject.h"
#include "Camera.h"
#include "Canvas.h"
#include "PlayStateHUD.h"
#include "MenuStateHUD.h"
#include "PauseStateHUD.h"

class Game;

class GameState
{
private:
	vector<GameObject*> items_ToDelete;

	void initializeCamera();

protected:
	Game* _gameptr = nullptr;
	b2World * _world = nullptr;

	list<GameObject*> _stages;

	Camera* _mainCamera = nullptr;
	Canvas* _canvas = nullptr;
	PlayStateHUD* _playHud = nullptr;
	MenuStateHUD* _menuHud = nullptr;
	PauseStateHUD* _pauseHud = nullptr;

public:
	GameState(Game* g);
	virtual ~GameState();

	virtual void render() const;
	virtual void update(const double& deltaTime);
	virtual void post_update();
	virtual bool handleEvent(const SDL_Event& event);

	virtual void addObject(GameObject* obj);
	virtual void destroyObject(GameObject* obj);

	inline virtual Camera* getMainCamera() const { return _mainCamera; }
	inline virtual PlayStateHUD* getPlayHUD() const { return _playHud; }
	inline virtual MenuStateHUD* getMenuHUD() const { return _menuHud; }
	inline virtual PauseStateHUD* getPauseHUD() const { return _pauseHud; }

	inline virtual list<GameObject*>& getObjects() { return _stages; }
	inline virtual void setCanvas(Canvas* canvas) { _canvas = canvas; }

	inline virtual void addCutScene() {};

	Vector2D getMousePositionInWorld() const;
	Vector2D getMousePositionOnScreen() const;
	void setMousePositionInWorld(Vector2D coord);
};