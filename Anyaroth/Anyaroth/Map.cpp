#include "Map.h"
#include "BodyComponent.h"
#include "MeleeEnemy.h"
#include "MartyrEnemy.h"
#include "DistanceStaticEnemy.h"
#include "DistanceDynamicEnemy.h"
#include "BomberEnemy.h"
#include "SpawnerEnemy.h"
#include "StaticSpawnerEnemy.h"
#include "Player.h"
#include "GunType_def.h"
#include <json.hpp>

using namespace nlohmann;

Map::Map(string filename, Game* game, PlayState* playstate, Texture* tileset, int coinValue) : _game(game), _playState(playstate), _coinValue(coinValue)
{
	_player = _playState->getPlayer();

	json j;
	fstream file;
	file.open(filename);
	if (file.is_open())
	{
		file >> j;
		j = j["layers"];
		for (int i = 0; i < j.size(); i++)
		{
			auto it = j[i].find("name");
			if (it != j[i].end())
			{
				if (*it == "Map" || *it == "Ground")
				{
					_layers.push_back(new Layer(filename, *it, tileset, game, *it));

					if(*it=="Ground")
						_layers.back()->addComponent<BodyComponent>();
				}
				else
				{
					_objectLayers[*it] = new ObjectLayer(filename, *it);
					_objectLayersNames.push_back(*it);
				}
			}
		}
		file.close();
	}
	else
		throw AnyarothError("No se ha encontrado el archivo introducido");

	createObjects();
}

Map::~Map()
{
	for (int j = 0; j < _layers.size(); j++)
		delete _layers[j];

	_layers.clear();

	for (int i = 0; i < _objectLayersNames.size(); i++)
		delete _objectLayers[_objectLayersNames[i]];

	_objectLayers.clear();

	for (int k = 0; k < _objects.size(); k++)
		delete _objects[k];

	_objects.clear();
}

void Map::createObjects()
{
	for (int i = 0; i < _objectLayersNames.size(); i++)
	{
		string name = _objectLayersNames[i];
		vector<Vector2D> pos = _objectLayers[name]->getObjectsPositions();

		for (int j = 0; j < pos.size(); j++)
		{
			if (name == "Player")
			{
				_player->setPlayerPosition(Vector2D(pos[j].getX() / M_TO_PIXEL, (pos[j].getY() - TILES_SIZE * 2) / M_TO_PIXEL));
			}
			else if (name == "Melee")
			{
				_objects.push_back(new MeleeEnemy(_player, _game, _playState, _game->getTexture("EnemyMelee"), Vector2D(pos[j].getX(), pos[j].getY() - TILES_SIZE * 2), "Enemy"));
			}
			else if (name == "Martyr")
			{
				_objects.push_back(new MartyrEnemy(_player, _game, _playState, _game->getTexture("EnemyMartyr"), Vector2D(pos[j].getX(), pos[j].getY() - TILES_SIZE * 2), "Enemy"));
			}
			else if (name == "DistanceStatic")
			{
				_objects.push_back(new DistanceStaticEnemy(_player, _game, _playState, _game->getTexture("EnemyMelee"), Vector2D(pos[j].getX(), pos[j].getY() - TILES_SIZE * 2), "Enemy", _playState->getEnemyPool()));
			}
			else if (name == "DistanceDynamic")
			{
				_objects.push_back(new DistanceDynamicEnemy(_player, _game, _playState, _game->getTexture("EnemyMelee"), Vector2D(pos[j].getX(), pos[j].getY() - TILES_SIZE * 2), "Enemy", _playState->getEnemyPool()));
			}
			else if (name == "Bomber")
			{
				_objects.push_back(new BomberEnemy(_player, _game, _playState, _game->getTexture("EnemyMartyr"), Vector2D(pos[j].getX(), pos[j].getY() - TILES_SIZE * 2), "Enemy", _playState->getEnemyPool()));
			}
			else if (name == "Spawner")
			{
				_objects.push_back(new SpawnerEnemy(_player, _game, _playState, _game->getTexture("EnemyMelee"), Vector2D(pos[j].getX(), pos[j].getY() - TILES_SIZE * 2), "Enemy"));
			}
			else if (name == "SpawnerStatic")
			{
				_objects.push_back(new StaticSpawnerEnemy(_player, _game, _playState, _game->getTexture("EnemyMelee"), Vector2D(pos[j].getX(), pos[j].getY() - TILES_SIZE * 2), "Enemy"));
			}
			else if (name == "Coin")
			{
				_objects.push_back(new Coin(_game, _game->getTexture("Coin"), Vector2D(pos[j].getX(), pos[j].getY() - TILES_SIZE), _coinValue));
			}
		}
	}
}

void Map::restartLevel()
{
	for (int i = 0; i < _objects.size(); i++)
		delete _objects[i];

	_objects.clear();
	createObjects();
}

bool Map::handleInput(const SDL_Event & event)
{
	GameComponent::handleInput(event);

	for (Layer* l : _layers)
		if (l->isActive())
			l->handleInput(event);

	for (GameComponent* o : _objects)
		if (o->isActive())
			o->handleInput(event);

	return false;
}

void Map::update(double time)
{
	GameComponent::update(time);

	for (Layer* l : _layers)
		if (l->isActive())
			l->update(time);

	for (GameComponent* o : _objects)
		if (o->isActive())
			o->update(time);
}

void Map::render(Camera * c) const
{
	GameComponent::render(c);

	for (Layer* l : _layers)
		if (l->isActive())
			l->render(c);

	for (GameComponent* o : _objects)
		if (o->isActive())
			o->render(c);
}