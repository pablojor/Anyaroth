#include "Tilemap.h"
#include "Camera.h"
#include "Game.h"
#include <json.hpp>


Tilemap::Tilemap(Game* game, Texture* tileSet) : GameObject(game)
{
	_tileSet = tileSet;

	_tileSize = _tileSet->getW() / _tileSet->getNumCols();
}


Tilemap::~Tilemap()
{
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
		data = data[0];

		auto it = data.find("height");
		if (it != data.end())
			height = *it;

		it = data.find("width");
		if (it != data.end())
			width = *it;

		it = data.find("data");
		if (it != data.end())
			data = *it;

		int indexCount = 1;
		_maxFils = height;
		_maxCols = width;

		for (int i = 0; i < _maxFils * _maxCols; i++)
		{
			if (data[i] != 0)
				_grid[i + 1] = { data[i] };
		}

		file.close();
	}
	else
		throw AnyarothError("No se ha encontrado el archivo introducido");
}
