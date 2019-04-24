#include "GameState.h"
#include "Game.h"

GameState::GameState(Game* g) : _gameptr(g), _world(g->getWorld())
{
	initializeCamera();
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

void GameState::update(const double& deltaTime)
{
	_mainCamera->update(deltaTime);

	for (GameObject* o : _stages)
		if (o->isActive())
			o->update(deltaTime);

	if (_canvas != nullptr)
		_canvas->update(deltaTime);
}

void GameState::post_update()
{
	int i = items_ToDelete.size() - 1;
	while (i >= 0)
	{
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

void GameState::addObject(GameObject* n)
{
	_stages.push_back(n);/*
	auto itFR = --(_stages.end());
	n->setItList(itFR);*/
}

void GameState::destroyObject(GameObject* obj)
{
	items_ToDelete.push_back(obj);
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