#include "GameObject.h"
#include <vector>
#include <map>
#include "Component.h"

using namespace std;

class InputComponent;
class PhysicsComponent;
class RenderComponent;

class GameComponent: public GameObject {

private:
	vector<InputComponent*> inputComp_;
	vector<PhysicsComponent*> physicsComp_;
	vector<RenderComponent*> renderComp_;

	map<string, Component*> _components;

	template<class ComponentType>
	ComponentType* add_component(string name)
	{
		if (_components.find(name) == _components.end())
		{
			ComponentType* c = new ComponentType(this);
			_components[name] = c;
			return c;
		}
		else cout << "Se ha intentado a�adir un componente ya existente" << endl;
		return nullptr;
	}

	void add_component(Component* c, string name) {	_components[name] = c; }

	template<class ComponentType>
	ComponentType* get_component(string name)
	{
		auto it = _components.find(name);
		ComponentType* c = nullptr;
		if(it != _components.end()) c = dynamic_cast<ComponentType*>(it->second);
		return c; //Ser� nullptr si no lo encuentra
	}

public:
	GameComponent();
	virtual ~GameComponent();

	virtual void handleInput(const SDL_Event& event);
	virtual void update();
	virtual void render() const;

	virtual void addInputComponent(InputComponent* ic);
	virtual void addPhysicsComponent(PhysicsComponent* pc);
	virtual void addRenderComponent(RenderComponent* rc);

	virtual void delInputComponent(InputComponent* ic);
	virtual void delPhysicsComponent(PhysicsComponent* pc);
	virtual void delRenderComponent(RenderComponent* rc);

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

	template<class ComponentType>
	ComponentType* getComponent()
	{
		ComponentType* c = get_component<ComponentType>(typeid(ComponentType).name());
		return c;
	}
};

