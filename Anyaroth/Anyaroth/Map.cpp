#include "Map.h"
#include "BodyComponent.h"
#include "Coin.h"
#include "MeleeEnemy.h"
#include "MartyrEnemy.h"
#include "DistanceStaticEnemy.h"
#include "DistanceDynamicEnemy.h"
#include "BomberEnemy.h"
#include "NormalSpawner.h"
#include "DistanceSpawner.h"
#include "StaticSpawnerEnemy.h"
#include "Player.h"
#include "GunType_def.h"
#include "BotonLanzaMisiles.h"
#include <json.hpp>

using namespace nlohmann;

Map::Map(string filename, Game* game, Player* player, Texture* tileset, BulletPool* bulletPool, PlayStateHUD* hud, int coinValue) : GameObject(game), _player(player), _bulletPool(bulletPool),  _hud(hud), _coinValue(coinValue)
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
	_faseMisil = 0;
	for (int i = 0; i < _objectLayers.size(); i++)
	{
		string name = _objectLayers[i]->getName();
		vector<pair<Vector2D, string>> objectData = _objectLayers[i]->getObjectsData();

		for (int j = 0; j < objectData.size(); j++)
		{
			Vector2D pos = objectData[j].first;
			string data = objectData[j].second;
			if (name == "Player")
			{
				_player->setPlayerPosition(Vector2D(pos.getX() / M_TO_PIXEL, (pos.getY() - TILES_SIZE * 2) / M_TO_PIXEL));
			}
			else if (name == "Melee")
			{
				_objects->addChild(new MeleeEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2)));
			}
			else if (name == "Martyr")
			{
				_objects->addChild(new MartyrEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2)));
			}
			else if (name == "DistanceStatic")
			{
				_objects->addChild(new DistanceStaticEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool));
			}
			else if (name == "DistanceDynamic")
			{
				_objects->addChild(new DistanceDynamicEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool));
			}
			else if (name == "Bomber")
			{
				_objects->addChild(new BomberEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool));
			}
			else if (name == "Spawner")
			{
				_objects->addChild(new NormalSpawner<MeleeEnemy>(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2)));
			}
			else if (name == "DistanceSpawner")
			{
				_objects->addChild(new DistanceSpawner<DistanceStaticEnemy>(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool));
			}
			else if (name == "SpawnerStatic")
			{
				_objects->addChild(new StaticSpawnerEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2)));
			}
			else if (name == "Coin")
			{
				_objects->addChild(new Coin(_game, _game->getTexture("Coin"), Vector2D(pos.getX(), pos.getY() - TILES_SIZE), _coinValue));
			}
			else if (name == "Boss1")
			{
				_boss1 = (new Boss1(_game, _player, Vector2D(pos.getX(), pos.getY()), _bulletPool));
				_objects->addChild(_boss1);
				_boss1->setBossPanel(_hud->getBossPanel());
			}
			else if (name == "Misiles")
			{
				_objects->addChild(new BotonLanzaMisiles(_game, _boss1, _game->getTexture("MissileTurret"), Vector2D(pos.getX(), pos.getY()), _faseMisil));
				_faseMisil++;
			}
			else if (name == "NPCs")
			{
				_n = new NPC(_game, Vector2D(pos.getX(), pos.getY()), _game->getDialogue(data));
				_n->setDialoguePanel(_hud->getDialoguePanel());
				_objects->addChild(_n);
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