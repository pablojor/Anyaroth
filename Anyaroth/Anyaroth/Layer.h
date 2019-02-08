#pragma once
#ifndef Layer_H
#define Layer_H

#include "Tile.h"
#include <string>
#include "Texture.h"
#include "GameComponent.h"

class Layer : public GameComponent{
public:
	Layer(string name, Texture* t, string filename);
	~Layer();
	void render(Uint32 time);
	//virtual void update(Uint32 time) {};
	//virtual void handleInput(Uint32 time, const SDL_Event& event) {};

	virtual void addInputComponent(InputComponent* ic);
	virtual void addPhysicsComponent(PhysicsComponent* pc);
	virtual void addRenderComponent(RenderComponent* rc);

	virtual void delInputComponent(InputComponent* ic);
	virtual void delPhysicsComponent(PhysicsComponent* pc);
	virtual void delRenderComponent(RenderComponent* rc);

protected:
	int type;
	Texture* tileset;
	vector<Tile*> tilemap;
};
#endif // Layer_H