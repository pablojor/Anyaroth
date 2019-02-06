#ifndef GAMECOMPONENT_H_
#define GAMECOMPONENT_H_

#include "GameObject.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include <vector>

using namespace std;
/*
 *
 */
class GameComponent: public GameObject {

private:
	vector<InputComponent*> inputComp_;
	vector<PhysicsComponent*> physicsComp_;
	vector<RenderComponent*> renderComp_;

protected:
	TransformComponent* transform;

public:
	GameComponent();
	virtual ~GameComponent();

	virtual void handleEvents(/*Uint32 time, */SDL_Event& event);
	virtual void update(/*Uint32 time*/);
	virtual void render(/*Uint32 time*/) const;

	virtual void addInputComponent(InputComponent* ic);
	virtual void addPhysicsComponent(PhysicsComponent* pc);
	virtual void addRenderComponent(RenderComponent* rc);

	virtual void delInputComponent(InputComponent* ic);
	virtual void delPhysicsComponent(PhysicsComponent* pc);
	virtual void delRenderComponent(RenderComponent* rc);
};

#endif /* GAMECOMPONENT_H_ */
