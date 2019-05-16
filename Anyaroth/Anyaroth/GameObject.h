#pragma once
#include "SDL.h"
#include "Box2D/Box2D.h"
#include "checkML.h"
#include "InputComponent.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include <vector>
#include <map>
#include <list>

#include "FileNotFoundError.h"
#include "FileFormatError.h"
#include "Vector2D.h"

using namespace std;

class Game;

class GameObject
{
private:
	vector<PhysicsComponent*> _physicsComp;
	vector<InputComponent*> _inputComp;
	vector<RenderComponent*> _renderComp;
	map<string, Component*> _components;

	GameObject* _parent = nullptr;
	list<GameObject*> _children; //lista de hijos del objeto

	b2World* _world = nullptr; //puntero a world
	bool _active = true;
	bool _dead = false;
	string _tag;

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

		return nullptr;
	}

	//Following Component
	template<class ComponentType>
	ComponentType* add_component(string name, GameObject* gc)
	{
		if (_components.find(name) == _components.end())
		{
			ComponentType* c = new ComponentType(this, gc);
			_components[name] = c;
			return c;
		}

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
protected:
	Game* _game = nullptr; //puntero a game
	bool _affectedByExternalForces = false;

	bool _isPlayer = false;

public:
	GameObject(Game* game, string tag = "");
	virtual ~GameObject();

	virtual bool handleEvent(const SDL_Event& event);
	virtual void update(double deltaTime);
	virtual void render(Camera* c) const;

	virtual void addInputComponent(InputComponent* ic);
	virtual void addPhysicsComponent(PhysicsComponent* pc);
	virtual void addRenderComponent(RenderComponent* rc);

	virtual void delInputComponent(InputComponent* ic);
	virtual void delPhysicsComponent(PhysicsComponent* pc);
	virtual void delRenderComponent(RenderComponent* rc);

	inline virtual vector<RenderComponent*>  getRenderComponents() const { return _renderComp; }
	inline virtual vector<InputComponent*>   getInputComponents() const { return _inputComp; }
	inline virtual vector<PhysicsComponent*>  getPhysicsComponents() const { return _physicsComp; }

	inline b2World* getWorld() const { return _world; }
	inline void setWorld(b2World* world) { _world = world; }

	virtual void beginCollision(GameObject* other, b2Contact* contact) {}
	virtual void endCollision(GameObject* other, b2Contact* contact) {}
	virtual void preCollision(GameObject* other, b2Contact* contact) {}
	virtual void postCollision(GameObject* other, b2Contact* contact) {}

	inline void addChild(GameObject* obj) { obj->_parent = this; _children.push_back(obj); }
	inline void addChildFront(GameObject* obj) { obj->_parent = this; _children.push_front(obj); }
	inline list<GameObject*>& getChildren()  { return _children; }
	void destroyAllChildren();
	inline GameObject* getParent() const { return _parent; }

	inline Game* getGame() const { return _game; }

	inline string getTag() const { return _tag; }
	inline void setTag(string  const &tag) { _tag = tag; }

	inline bool isActive() const { return _active; }
	inline bool isPlayer() const { return _isPlayer; }
	inline void setActive(bool active) { _active = active; }
	virtual inline void setStopped(bool value) {}
	virtual inline void setStunned(bool value) {}
	virtual inline void setInputFreezed(bool b) {}

	inline bool isDead() const { return _dead; }
	inline void setDead(bool dead) { _dead = dead; }

	virtual int getDamage() const { return 0; }
	virtual void subLife(int damage) {}

	inline Camera* getCamera() const;

	Vector2D getPositionOnCamera();

	inline virtual int getValue() const { return -1; }

	inline bool isAffectedByExternalForces() const { return _affectedByExternalForces; }

	void destroy();
	
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
			_components[name] = ct;
	}

	template<class ComponentType>
	void deleteComponent(ComponentType* ct)
	{
		string name = typeid(*ct).name();
		if (_components.find(name) != _components.end())
			_components.erase(name);
	}

	//Para el Following Component
	template<class ComponentType>
	ComponentType* addComponent(GameObject* gc)
	{
		return add_component<ComponentType>(typeid(ComponentType).name(), gc);
	}

	template<class ComponentType>
	ComponentType* getComponent()
	{
		return get_component<ComponentType>(typeid(ComponentType).name());
	}
};