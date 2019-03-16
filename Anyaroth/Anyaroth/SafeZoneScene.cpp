#include "SafeZoneScene.h"
#include "Game.h"


SafeZoneScene::SafeZoneScene(Game* g, Player* ply, string file) : _player(ply), GameState::GameState(g)
{
	_shop = new Shop();

	_stages.push_back(_player);
	_stages.push_back(_shop);

	//loadFromFile(file);
}

void SafeZoneScene::loadFromFile(string s)
{
	string file = FILES_PATH + s + ".txt";
	ifstream input;
	input.open(file);

	if (!input.is_open()) cout << "No se ha encontrado el archivo " + file << endl;
	else
	{
		_shop->loadFromFile(input);
	}
}

SafeZoneScene::~SafeZoneScene()
{
}

void SafeZoneScene::render() const
{
	GameState::render();
}

void SafeZoneScene::update(double time)
{
	GameState::update(time);
}

bool SafeZoneScene::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);

	bool handled = false;
	return handled;
}
