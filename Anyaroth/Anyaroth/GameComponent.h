#ifndef GAMECOMPONENT_H_
#define GAMECOMPONENT_H_

#include "GameObject.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "Component.h"
#include "Transform.h"
#include <vector>

using namespace std;
/*
 *
 */
class GameComponent: public GameObject {
public:
	GameComponent();
	virtual ~GameComponent();

	virtual void handleEvents(/*Uint32 time, */SDL_Event& event);
	virtual void update(/*Uint32 time*/);
	virtual void render(/*Uint32 time*/) const;

	virtual void addInputComponent(InputComponent* ic);
	virtual void addPhysicsComponent(PhysicsComponent* pc);
	virtual void addRenderComponent(RenderComponent* rc);
	virtual void addComponent(Component* c);

	virtual void delInputComponent(InputComponent* ic);
	virtual void delPhysicsComponent(PhysicsComponent* pc);
	virtual void delRenderComponent(RenderComponent* rc);
	virtual void delComponent(Component* c);

	Transform* getTransform() { return transform; }

private:
	vector<InputComponent*> inputComp_;
	vector<PhysicsComponent*> physicsComp_;
	vector<RenderComponent*> renderComp_;
	vector<Component*> extraComp_;
	//Temporal
	Transform* transform = new Transform(this);
};

#endif /* GAMECOMPONENT_H_ */
