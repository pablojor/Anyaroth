#include "Tilemap.h"
#include "Camera.h"
#include "Game.h"
#include <json.hpp>

using namespace nlohmann;

Tilemap::Tilemap(Game* game, Texture* tileSet) : GameObject(game)
{
	_tileSet = tileSet;
	_tileSize = _tileSet->getW() / _tileSet->getNumCols();
}

Tilemap::~Tilemap()
{
	for (b2Body* b : _colliders)
		_game->getWorld()->DestroyBody(b);
	_colliders.clear();
}

void Tilemap::update(const double & deltaTime)
{
}

void Tilemap::render(Camera * c) const
{
	auto camPos = c->getCameraPosition();
	auto camSize = c->getCameraSize();

	int pXIndex = camPos.getX() / _tileSize + 1;
	int pYIndex = camPos.getY() / _tileSize + 1;
	int colsInCam = camSize.getX() / _tileSize + 1;
	int filsInCam = camSize.getY() / _tileSize + 1;

	int pIndex = pXIndex + (pYIndex - 1) * _maxCols;

	//Por cada fila que quepa en camara
	while (filsInCam > 0)
	{
		//Por cada una de las columnas llevas de tiles
		auto beginOfFil = _grid.upper_bound(pIndex - 1);
		auto endOfFil = _grid.lower_bound(pIndex + colsInCam);
		if (beginOfFil != _grid.end() && (*beginOfFil).first < pIndex + colsInCam - 1)
		{
			while (beginOfFil != endOfFil)
			{
				//Fila y columna de la textura
				Tile t = (*beginOfFil).second;
				int row = (t.index - 1) / _tileSet->getNumCols();
				int col = (t.index - 1) % _tileSet->getNumCols();

				int y = (*beginOfFil).first / (_maxCols - 1);
				int x = ((*beginOfFil).first % _maxCols) - 1;

				SDL_Rect destRect = { x * _tileSize, y * _tileSize, _tileSize, _tileSize };

				SDL_Rect winRect = { destRect.x * GAME_RESOLUTION_X / c->getCameraSize().getX(), destRect.y * GAME_RESOLUTION_Y / c->getCameraSize().getY(),
					destRect.w * GAME_RESOLUTION_X / c->getCameraSize().getX() + 1, destRect.h * GAME_RESOLUTION_Y / c->getCameraSize().getY() + 1 }; //+1 para el tema del Zoom

				_tileSet->renderFrame(winRect, row, col);
				beginOfFil++;
			}
		}
		filsInCam--;
		pIndex += _maxCols;
	}
}

void Tilemap::loadTileMap(const string & filename)
{
	nlohmann::json data;
	//_tilemap.clear();
	fstream file;
	file.open(filename);
	if (file.is_open())
	{
		file >> data;
		data = data["layers"];
		
		int index, height = 0, width = 0;
		string type, name;
		for (int i = 0; i < data.size(); i++)
		{
			json layer = data[i];

			auto it = layer.find("type");
			if (it != layer.end())
				type = (*it).get<string>();

			if (type == "tilelayer")
			{
				it = layer.find("name");
				if (it != layer.end())
					name = (*it).get<string>();

				it = layer.find("height");
				if (it != layer.end())
					height = *it;

				it = layer.find("width");
				if (it != layer.end())
					width = *it;

				it = layer.find("data");
				if (it != layer.end())
					layer = *it;

				int indexCount = 1;
				_maxFils = height;
				_maxCols = width;

				for (int i = 0; i < _maxFils * _maxCols; i++)
				{
					if (layer[i] != 0)
					{
						_grid[i + 1] = Tile(layer[i]);

						if (name == "Ground" || name == "Platform" || name == "Door")
						{
							_grid[i + 1].setTag(name);

							int y = (i + 1) / (_maxCols - 1);
							int x = ((i + 1) % _maxCols) - 1;

							b2BodyDef bodydef;
							bodydef.type = b2_staticBody;
							bodydef.position = b2Vec2(x*_tileSize / M_TO_PIXEL + 1, y*_tileSize / M_TO_PIXEL + 1);
							bodydef.angle = 0.0;
							b2Body* body = _game->getWorld()->CreateBody(&bodydef);

							b2PolygonShape shape;
							shape.SetAsBox(_tileSize / (M_TO_PIXEL*2), _tileSize / (M_TO_PIXEL*2));

							b2FixtureDef fixture;
							fixture.shape = &shape;
							fixture.density = 1;
							fixture.restitution = 0;
							fixture.friction = 0.001;

							body->CreateFixture(&fixture);
							body->SetUserData(&_grid[i + 1]);
							body->SetFixedRotation(true);

							_colliders.push_back(body);
						}
					}
				}
			}
		}

		file.close();
	}
	else
		throw AnyarothError("No se ha encontrado el archivo introducido");
}