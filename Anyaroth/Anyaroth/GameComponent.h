#ifndef GAMECOMPONENT_H_
#define GAMECOMPONENT_H_

#include "GameObject.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
//#include "TransformComponent.h"
#include "Component.h"
#include <vector>
#include <map>

using namespace std;
/*
 *
 */
class GameComponent: public GameObject {

private:
	vector<InputComponent*> inputComp_;
	vector<PhysicsComponent*> physicsComp_;
	vector<RenderComponent*> renderComp_;

	map<string, Component*> _components;

	template<class ComponentType>
	void add_component(string name)
	{
		if (_components.find(name) == _components.end())
		{
			Component* c = new ComponentType();
			_components[name] = c;
		}
		else cout << "Se ha intentado añadir un componente ya existente" << endl;
	}

	template<class ComponentType>
	ComponentType* get_component(string name)
	{
		auto it = _components.find(name);
		ComponentType* c = dynamic_cast<ComponentType*>(it->second);
		return c; //Será nullptr si no lo encuentras
	}

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

	template<class ComponentType>
	void addComponent() 
	{
		add_component<ComponentType>(typeid(ComponentType).name());
	}

	template<class ComponentType>
	ComponentType* getComponent()
	{
		ComponentType* c = get_component<ComponentType>(typeid(ComponentType).name());
		return (c == nullptr ? throw exception("Componente pedido no existente") : c);
	}
};

#endif /* GAMECOMPONENT_H_ */
