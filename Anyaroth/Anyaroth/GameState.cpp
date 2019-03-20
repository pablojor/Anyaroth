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
		delete _canvas;

	for (GameObject* o : _stages)
		delete o;
}

void GameState::render() const
{
	_mainCamera->render();

	for (GameObject* o : _stages)
		o->render(_mainCamera);

	if (_canvas != nullptr)
		_canvas->render();
}

void GameState::update(double time)
{
	_mainCamera->update(time);

	for (GameObject* o : _stages)
		o->update(time);

	if (_canvas != nullptr)
		_canvas->update(time);
}

bool GameState::handleEvents(SDL_Event& e)
{
	bool handled = false;
	auto it = _stages.begin();

	while (!handled && it != _stages.end())
	{
		if ((*it)->handleInput(e))
			handled = true;
		else
			it++;
	}

	if (_canvas != nullptr && !handled)
		_canvas->handleEvent(e);

	return handled;
}

Vector2D GameState::getMousePositionInWorld() const
{
	int winWidth = 0;	int winHeight = 0;
	SDL_GetWindowSize(_gameptr->getWindow(), &winWidth, &winHeight);

	//Cogemos su posicion en pantalla
	int xMousePos = 0;	int yMousePos = 0;
	SDL_GetMouseState(&xMousePos, &yMousePos);

	xMousePos = (xMousePos * GAME_RESOLUTION_X) / winWidth;
	yMousePos = (yMousePos * GAME_RESOLUTION_Y) / winHeight;

	//Lo convertimos en su posicion en el mundo
	xMousePos += getMainCamera()->getCameraPosition().getX();
	yMousePos += getMainCamera()->getCameraPosition().getY();

	return Vector2D(xMousePos, yMousePos);
}

void GameState::initializeCamera()
{
	_mainCamera = new Camera();
	_mainCamera->setCameraPosition(0, 0);
	_mainCamera->setCameraSize(GAME_RESOLUTION_X, GAME_RESOLUTION_Y);
}