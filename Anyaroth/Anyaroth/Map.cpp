#include "Map.h"
#include "BodyComponent.h"
#include "MeleeEnemy.h"
#include "MartyrEnemy.h"
#include "DistanceStaticEnemy.h"
#include "DistanceDynamicEnemy.h"
#include "StaticFlyingEnemy.h"
#include "BomberEnemy.h"
#include "NormalSpawner.h"
#include "DistanceSpawner.h"
#include "StaticSpawnerEnemy.h"
#include "Player.h"
#include "NPC.h"
#include "Shop.h"
#include "GunType_def.h"
#include "BotonLanzaMisiles.h"
#include <json.hpp>

using namespace nlohmann;

Map::Map(string filename, Game* game, Player* player, Texture* tileset, BulletPool* bulletPool, PlayStateHUD* hud) : GameObject(game), _player(player), _bulletPool(bulletPool),  _hud(hud)
{
	_tilemap = new Tilemap(game, tileset);
	_tilemap->loadTileMap(filename);
	addChild(_tilemap);

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
				if (*it != "Map" && *it != "Ground" && *it != "Platform" && *it != "Door")
					_objectLayers.push_back(new ObjectLayer(filename, *it));
				else if (*it == "Map")
				{
					it = j[i].find("height");
					_height = *it;
					_height = _height * TILES_SIZE;

					it = j[i].find("width");
					_width = *it;
					_width = _width * TILES_SIZE;
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
	for (int i = 0; i < _objectLayers.size(); i++)
		delete _objectLayers[i];

	_objectLayers.clear();
}

void Map::createObjects()
{
	_misilFase = 0;

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
				_objects->addChild(new MeleeEnemy(_game, _player, Vector2D(pos.getX() - TILES_SIZE, pos.getY() - TILES_SIZE * 2)));
			}
			else if (name == "Martyr")
			{
				_objects->addChild(new MartyrEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2)));
			}
			else if (name == "DistanceStatic")
			{
				_objects->addChild(new DistanceStaticEnemy(_game, _player, Vector2D(pos.getX() /*- TILES_SIZE*/, pos.getY() - TILES_SIZE * 2), _bulletPool));
			}
			else if (name == "FlyingDistance")
			{
				_objects->addChild(new StaticFlyingEnemy(_game, _player, Vector2D(pos.getX() - TILES_SIZE, pos.getY() - TILES_SIZE * 2), _bulletPool));
			}
			else if (name == "DistanceDynamic")
			{
				_objects->addChild(new DistanceDynamicEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool));
			}
			else if (name == "Spawner")
			{
				_objects->addChild(new StaticSpawnerEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2)));
			}
			else if (name == "MeleeShip")
			{
				_objects->addChild(new NormalSpawner<MeleeEnemy>(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2)));
			}
			else if (name == "DistanceStaticShip")
			{
				_objects->addChild(new DistanceSpawner<DistanceStaticEnemy>(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool));
			}
			else if (name == "Bomber")
			{
				_objects->addChild(new BomberEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool));
			}
			else if (name == "Misil")
			{
				_objects->addChild(new BotonLanzaMisiles(_game, _spenta, _game->getTexture("MissileTurret"), Vector2D(pos.getX() - TILES_SIZE, pos.getY() - TILES_SIZE * 2.8), _misilFase));
				_misilFase++;
			}
			else if (name == "Boss1")
			{
				_spenta = (new Boss1(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool));
				_objects->addChild(_spenta);
				_spenta->setBossPanel(_hud->getBossPanel());
			}
			else if (name == "NPC")
			{
				auto npc = new NPC(_game, Vector2D(pos.getX() - TILES_SIZE, pos.getY() - TILES_SIZE * 2), _game->getDialogue(data));
				npc->setDialoguePanel(_hud->getDialoguePanel());
				_objects->addChild(npc);
			}
			else if (name == "Shop")
			{
				auto tienda = new Shop(_game, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2.6), _hud->getShop());
				_objects->addChild(tienda);
			}
		}
	}
}

void Map::restartLevel()
{
	if (_objects->getChildren().size() != 0)
	{
		_objects->destroyAllChildren();
		createObjects();
	}
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