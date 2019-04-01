#pragma once
#include "Tile.h"
#include <string>

class Layer : public GameObject
{
protected:
	vector<Tile*> _tilemap;

public:
	Layer(string filename, string name, Texture* t, Game* g, string tag);
	~Layer();

	void render(Camera* c) const;
	inline vector<Tile*> getTilemap() const { return _tilemap; }

	template<typename ComponentType>
	ComponentType* addComponent() //Redefino addComponent() para que, en vez de añadir el componente al layer, lo añada a cada tile
	{
		for (Tile* t : _tilemap)
			t->addComponent<ComponentType>();

		return nullptr;
	}
};