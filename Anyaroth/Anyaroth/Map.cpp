#include "Map.h"
#include "BodyComponent.h"
#include "Coin.h"
#include "MeleeEnemy.h"
#include "MartyrEnemy.h"
#include "DistanceStaticEnemy.h"
#include "DistanceDynamicEnemy.h"
#include "BomberEnemy.h"
#include "SpawnerEnemy.h"
#include "StaticSpawnerEnemy.h"
#include "GunType_def.h"
#include "BotonLanzaMisiles.h"
#include <json.hpp>

using namespace nlohmann;

Map::Map(string filename, Game* game, Player* player, Texture* tileset, BulletPool* bulletPool, ExplosiveBulletPool* explosivePool, BouncingBulletPool* bouncingPool, PlayStateHUD* hud, int coinValue) : GameObject(game), _player(player), _bulletPool(bulletPool), _explosivePool(explosivePool), _bouncingPool(bouncingPool), _hud(hud), _coinValue(coinValue)
{
	_layers = new GameObject(_game);
	addChild(_layers);

	_objects = new GameObject(_game);
	addChild(_objects);

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
				if (*it == "Map" || *it == "Ground" || *it == "Platform")
				{
					auto layer = new Layer(filename, *it, tileset, game, *it);
					_layers->addChild(layer);

					if(*it!="Map")
						layer->addComponent<BodyComponent>();
				}
				else
					_objectLayers.push_back(new ObjectLayer(filename, *it));
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
	for (int i = 0; i < _objectLayers.size(); i++)
		delete _objectLayers[i];

	_objectLayers.clear();
}

void Map::createObjects()
{
	for (int i = 0; i < _objectLayers.size(); i++)
	{
		string name = _objectLayers[i]->getName();
		vector<Vector2D> pos = _objectLayers[i]->getObjectsPositions();

		for (int j = 0; j < pos.size(); j++)
		{
			if (name == "Player")
			{
				_player->setPlayerPosition(Vector2D(pos[j].getX() / M_TO_PIXEL, (pos[j].getY() - TILES_SIZE * 2) / M_TO_PIXEL));
			}
			else if (name == "Melee")
			{
				_objects->addChild(new MeleeEnemy(_game, _player, Vector2D(pos[j].getX(), pos[j].getY() - TILES_SIZE * 2)));
			}
			else if (name == "Martyr")
			{
				_objects->addChild(new MartyrEnemy(_game, _player, Vector2D(pos[j].getX(), pos[j].getY() - TILES_SIZE * 2)));
			}
			else if (name == "DistanceStatic")
			{
				_objects->addChild(new DistanceStaticEnemy(_game, _player, Vector2D(pos[j].getX(), pos[j].getY() - TILES_SIZE * 2), _bulletPool));
			}
			else if (name == "DistanceDynamic")
			{
				_objects->addChild(new DistanceDynamicEnemy(_game, _player, Vector2D(pos[j].getX(), pos[j].getY() - TILES_SIZE * 2), _bulletPool));
			}
			else if (name == "Bomber")
			{
				_objects->addChild(new BomberEnemy(_game, _player, Vector2D(pos[j].getX(), pos[j].getY() - TILES_SIZE * 2), _explosivePool));
			}
			else if (name == "Spawner")
			{
				_objects->addChild(new SpawnerEnemy(_game, _player, Vector2D(pos[j].getX(), pos[j].getY() - TILES_SIZE * 2)));
			}
			else if (name == "SpawnerStatic")
			{
				_objects->addChild(new StaticSpawnerEnemy(_game, _player, Vector2D(pos[j].getX(), pos[j].getY() - TILES_SIZE * 2)));
			}
			else if (name == "Coin")
			{
				_objects->addChild(new Coin(_game, _game->getTexture("Coin"), Vector2D(pos[j].getX(), pos[j].getY() - TILES_SIZE), _coinValue));
			}
			else if (name == "Boss1")
			{
				_boss1 = (new Boss1(_game, _player, Vector2D(pos[j].getX(), pos[j].getY()), _bulletPool, _explosivePool, _bouncingPool));
				_objects->addChild(_boss1);
				_boss1->setBossPanel(_hud->getBossPanel());
			}
			else if (name == "Misiles")
			{
				_objects->addChild(new BotonLanzaMisiles(_game, _boss1, _game->getTexture("EnemyMartyr"), Vector2D(pos[j].getX(), pos[j].getY())));
			}
		}
	}
}

void Map::restartLevel()
{
	_objects->destroyAllChildren();
	createObjects();
}

bool Map::handleEvent(const SDL_Event & event)
{
	GameObject::handleEvent(event);
	return false;
}

void Map::update(const double& deltaTime)
{
	GameObject::update(deltaTime);
}

void Map::render(Camera * c) const
{
	GameObject::render(c);
}