#pragma once
#include <string>
#include "Tile.h"

class Layer : public GameComponent 
{
	protected:
		Texture* _tileset;
		vector<Tile*> _tilemap;
	public:
		Layer(string name, Texture* t, string filename, Game* g);
		~Layer();

		void render() const;

		vector<Tile*> getTilemap() { return _tilemap; };


		template<typename ComponentType>
		ComponentType* addComponent() //Redefino addComponent() para que, en vez de anyadir el componente a la layer, lo anyade a cada tile
		{
			for (Tile* t : _tilemap)
			{
				t->addComponent<ComponentType>();
			}

			return nullptr;
			//return add_component<ComponentType>(typeid(ComponentType).name());
		}
};