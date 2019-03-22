#pragma once
#include <list>
#include <vector>
#include "GameObject.h"
#include "Camera.h"
#include "Canvas.h"

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

public:
	GameState(Game* g);
	virtual ~GameState();

	virtual void render() const;
	virtual void update(const double& deltaTime);
	void post_update();
	virtual bool handleEvent(const SDL_Event& event);

	void addObject(GameObject* obj);
	void destroyObject(GameObject* obj);

	inline virtual Camera* getMainCamera() const { return _mainCamera; }
	inline virtual list<GameObject*>& getObjects() { return _stages; }
	inline virtual void setCanvas(Canvas* canvas) { _canvas = canvas; }
	Vector2D getMousePositionInWorld() const;
};