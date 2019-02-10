#pragma once
#include <string>
#include "Tile.h"

class Layer : public GameComponent {
public:
	Layer(string name, Texture* t, string filename);
	~Layer();
	void render() const;

protected:
	//int type;
	Texture* tileset;
	vector<Tile*> tilemap;
public:
	template<class ComponentType>
	ComponentType* addComponent() //Redefino addComponent() para que, en vez de anyadir el componente a la layer, lo anyade a cada tile
	{
		for (Tile* t : tilemap)
		{
			t->addComponent<ComponentType>();
		}

		return nullptr;
		//return add_component<ComponentType>(typeid(ComponentType).name());
	}

	vector<Tile*> getTilemap() { return tilemap; };
};