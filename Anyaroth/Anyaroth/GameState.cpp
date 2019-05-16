#include "GameState.h"
#include "Game.h"
#include "CutScene.h"

GameState::GameState(Game* g) : _gameptr(g)
{
	_hasToStart = true;
	_gameLoaded = false;
	initializeCamera();

	//---Create world
	_world = new b2World(b2Vec2(0.0, 9.8));

	//Debugger
	_debugger.getRenderer(_gameptr->getRenderer());
	_debugger.getTexture(_gameptr->getTexture("Box"));
	_debugger.SetFlags(b2Draw::e_shapeBit);
	_debugger.getCamera(_mainCamera);

	//Collisions and debugger
	_world->SetContactListener(&_colManager);
	_world->SetDebugDraw(&_debugger);
}

GameState::~GameState()
{
	delete _mainCamera;

	if (_canvas != nullptr)
	{
		delete _canvas;
		_canvas = nullptr;
	}

	for (GameObject* o : _stages)
		delete o;

	delete _world;
}

void GameState::render() const
{
	_mainCamera->render();

	for (GameObject* o : _stages)
		if (o->isActive())
			o->render(_mainCamera);

	if (_canvas != nullptr)
		_canvas->render();

	_mainCamera->last_render();
}

void GameState::update(double deltaTime)
{
	_mainCamera->update(deltaTime);

	for (GameObject* o : _stages)
		if (o->isActive())
			o->update(deltaTime);

	if (_canvas != nullptr)
		_canvas->update(deltaTime);

	if (_cutScene != nullptr)
	{
		if (_cutScene->isPlaying())
			_cutScene->update(deltaTime);
		else
		{
			delete _cutScene;
			_cutScene = nullptr;
		}
	}
}

void GameState::post_update()
{
	int i = items_ToDelete.size() - 1;
	while (i >= 0)
	{
		GameObject* parent = items_ToDelete[i]->getParent();
		if (parent != nullptr)
			parent->getChildren().remove(items_ToDelete[i]);

		delete items_ToDelete[i];
		_stages.remove(items_ToDelete[i]);
		items_ToDelete.pop_back();
		i--;
	}
}

bool GameState::handleEvent(const SDL_Event& event)
{
	bool handled = false;
	auto it = _stages.begin();

	while (!handled && it != _stages.end())
	{
		if ((*it)->handleEvent(event))
			handled = true;
		else
			it++;
	}

	if (_canvas != nullptr && !handled)
		_canvas->handleEvent(event);

	return handled;
}

bool GameState::pre_handleEvent()
{
	return _mainCamera->pre_handleEvent();
}

void GameState::updateWorld(float timestep, int velocityIterations, int positionIterations)
{
	if(_world != nullptr)
		_world->Step(timestep, velocityIterations, positionIterations);
}

void GameState::addObject(GameObject* n)
{
	_stages.push_back(n);
}

void GameState::destroyObject(GameObject* obj)
{
	auto it = std::find(items_ToDelete.begin(), items_ToDelete.end(), obj);
	if(it == items_ToDelete.end())
		items_ToDelete.push_back(obj);
}

void GameState::addCutScene(CutScene * cutScene)
{
	if (_cutScene != nullptr) 
		delete _cutScene; 
	_cutScene = cutScene;
}

Vector2D GameState::getMousePositionInWorld() const
{
	int winWidth = 0;	int winHeight = 0;
	SDL_GetWindowSize(_gameptr->getWindow(), &winWidth, &winHeight);

	//Sacamos la resolucion real que tiene el juego en la ventana
	int gameWidth; int gameHeight;
	gameWidth = GAME_RESOLUTION_X * winHeight / GAME_RESOLUTION_Y;

	if (gameWidth > winWidth)
	{
		gameHeight = GAME_RESOLUTION_Y * winWidth / GAME_RESOLUTION_X;
		gameWidth = GAME_RESOLUTION_X * gameHeight / GAME_RESOLUTION_Y;
	}
	else
		gameHeight = GAME_RESOLUTION_Y * gameWidth / GAME_RESOLUTION_X;

	//Bordes negros
	int xBorder = winWidth - gameWidth;
	int yBorder = winHeight - gameHeight;

	//Cogemos su posicion en pantalla
	int xMousePos = 0;	int yMousePos = 0;
	SDL_GetMouseState(&xMousePos, &yMousePos);

	xMousePos -= xBorder / 2;
	yMousePos -= yBorder / 2;

	xMousePos = (xMousePos * _mainCamera->getCameraSize().getX()) / gameWidth;
	yMousePos = (yMousePos * _mainCamera->getCameraSize().getY()) / gameHeight;

	//Lo convertimos en su posicion en el mundo
	xMousePos += getMainCamera()->getCameraPosition().getX();
	yMousePos += getMainCamera()->getCameraPosition().getY();

	return Vector2D(xMousePos, yMousePos);
}

Vector2D GameState::getMousePositionOnScreen() const
{
	int winWidth = 0;	int winHeight = 0;
	SDL_GetWindowSize(_gameptr->getWindow(), &winWidth, &winHeight);

	//Sacamos la resolucion real que tiene el juego en la ventana
	int gameWidth; int gameHeight;
	gameWidth = GAME_RESOLUTION_X * winHeight / GAME_RESOLUTION_Y;

	if (gameWidth > winWidth)
	{
		gameHeight = GAME_RESOLUTION_Y * winWidth / GAME_RESOLUTION_X;
		gameWidth = GAME_RESOLUTION_X * gameHeight / GAME_RESOLUTION_Y;
	}
	else
		gameHeight = GAME_RESOLUTION_Y * gameWidth / GAME_RESOLUTION_X;

	//Bordes negros
	int xBorder = winWidth - gameWidth;
	int yBorder = winHeight - gameHeight;

	//Cogemos su posicion en pantalla
	int xMousePos = 0;	int yMousePos = 0;
	SDL_GetMouseState(&xMousePos, &yMousePos);

	xMousePos -= xBorder / 2;
	yMousePos -= yBorder / 2;

	xMousePos = (xMousePos * GAME_RESOLUTION_X) / gameWidth;
	yMousePos = (yMousePos * GAME_RESOLUTION_Y) / gameHeight;

	return Vector2D(xMousePos, yMousePos);
}

Vector2D GameState::getMousePositionOnCamera() const
{
	Vector2D camPos = getMousePositionInWorld() - _mainCamera->getCameraPosition();
	Vector2D mousePos = Vector2D(camPos.getX() * CAMERA_RESOLUTION_X / _mainCamera->getCameraSize().getX(), camPos.getY() * CAMERA_RESOLUTION_Y / _mainCamera->getCameraSize().getY());

	return mousePos;
}

void GameState::setMousePositionInWorld(Vector2D coord)
{
	int winWidth = 0;	int winHeight = 0;
	SDL_GetWindowSize(_gameptr->getWindow(), &winWidth, &winHeight);

	//Sacamos la resolucion real que tiene el juego en la ventana
	int gameWidth; int gameHeight;
	gameWidth = GAME_RESOLUTION_X * winHeight / GAME_RESOLUTION_Y;

	if (gameWidth > winWidth)
	{
		gameHeight = GAME_RESOLUTION_Y * winWidth / GAME_RESOLUTION_X;
		gameWidth = GAME_RESOLUTION_X * gameHeight / GAME_RESOLUTION_Y;
	}
	else
		gameHeight = GAME_RESOLUTION_Y * gameWidth / GAME_RESOLUTION_X;

	//Bordes negros
	int xBorder = winWidth - gameWidth;
	int yBorder = winHeight - gameHeight;

	//Cogemos su posicion en pantalla
	int xMousePos = coord.getX();	int yMousePos = coord.getY();
	
	xMousePos -= getMainCamera()->getCameraPosition().getX();
	yMousePos -= getMainCamera()->getCameraPosition().getY();

	xMousePos = xMousePos * gameWidth / getMainCamera()->getCameraSize().getX();
	yMousePos = yMousePos * gameHeight / getMainCamera()->getCameraSize().getY();

	xMousePos += xBorder/2;
	yMousePos += yBorder/2;

	SDL_WarpMouseInWindow(_gameptr->getWindow(), xMousePos, yMousePos);
}

void GameState::initializeCamera()
{
	_mainCamera = new Camera(_gameptr);
	_mainCamera->setCameraPosition(0, 0);
	_mainCamera->setCameraSize(CAMERA_RESOLUTION_X, CAMERA_RESOLUTION_Y);
}