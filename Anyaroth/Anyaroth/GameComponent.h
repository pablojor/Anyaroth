#pragma once
#include "GameObject.h"
#include "Component.h"
#include <vector>
#include <map>
#include <Box2D/Box2D.h>

using namespace std;

class InputComponent;
class PhysicsComponent;
class RenderComponent;
class Game;

class GameComponent : public GameObject
{
private:
	vector<InputComponent*> _inputComp;
	vector<PhysicsComponent*> _physicsComp;
	vector<RenderComponent*> _renderComp;
	map<string, Component*> _components;

	b2World* _world = nullptr;
	string _tag;
	vector<GameComponent*> _children; //vector de hijos del objeto

	Game* _game = nullptr; //puntero a game

	bool _active = false;

	inline void add_component(Component* c, string name) { _components[name] = c; }

	template<class ComponentType>
	ComponentType* add_component(string name)
	{
		if (_components.find(name) == _components.end())
		{
			ComponentType* c = new ComponentType(this);
			_components[name] = c;
			return c;
		}
		else
			cout << "Se ha intentado anyadir un componente ya existente" << endl;

		return nullptr;
	}

	//Following Component
	template<class ComponentType>
	ComponentType* add_component(string name, GameComponent* gc)
	{
		if (_components.find(name) == _components.end())
		{
			ComponentType* c = new ComponentType(this, gc);
			_components[name] = c;
			return c;
		}
		else
			cout << "Se ha intentado anyadir un componente ya existente" << endl;

		return nullptr;
	}

	template<class ComponentType>
	ComponentType* get_component(string name)
	{
		auto it = _components.find(name);
		ComponentType* c = nullptr;
		if (it != _components.end())
			c = dynamic_cast<ComponentType*>(it->second);
		return c; //Sera nullptr si no lo encuentra
	}

public:
	GameComponent();
	GameComponent(Game* g, string tag = "");
	virtual ~GameComponent();

	virtual bool handleInput(const SDL_Event& event);
	virtual void update(double time);
	virtual void render(Camera* c) const;

	virtual void addInputComponent(InputComponent* ic);
	virtual void addPhysicsComponent(PhysicsComponent* pc);
	virtual void addRenderComponent(RenderComponent* rc);

	virtual void delInputComponent(InputComponent* ic);
	virtual void delPhysicsComponent(PhysicsComponent* pc);
	virtual void delRenderComponent(RenderComponent* rc);

	b2World* getWorld() const;
	inline void setWorld(b2World* world) { _world = world; }

	virtual void beginCollision(GameComponent* other, b2Contact* contact) {}
	virtual void endCollision(GameComponent* other, b2Contact* contact) {}
	virtual void preCollision(GameComponent* other, b2Contact* contact) {}
	virtual void postCollision(GameComponent* other, b2Contact* contact) {}

	void addChild(GameComponent* obj);

	inline Game* getGame() const { return _game; }

	inline string getTag() const { return _tag; }
	inline void setTag(string  const &tag) { _tag = tag; }

	inline bool isActive() const { return _active; }
	inline void setActive(bool active) { _active = active; }

	template<class ComponentType>
	ComponentType* addComponent()
	{
		return add_component<ComponentType>(typeid(ComponentType).name());
	}

	//De momento SOLO es para la TEXTURA
	template<class ComponentType>
	void addComponent(ComponentType* ct)
	{
		string name = typeid(*ct).name();
		if (_components.find(name) == _components.end())
		{
			_components[name] = ct;
		}
	}

	//Para el Following Component
	template<class ComponentType>
	ComponentType* addComponent(GameComponent* gc)
	{
		return add_component<ComponentType>(typeid(ComponentType).name(), gc);
	}

	template<class ComponentType>
	ComponentType* getComponent()
	{
		return get_component<ComponentType>(typeid(ComponentType).name());
	}
};