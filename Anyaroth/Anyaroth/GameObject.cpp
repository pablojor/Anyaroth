#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(Game* game, string tag) : _game(game), _inputComp(), _physicsComp(), _renderComp(), _tag(tag)
{
	if (game != nullptr) _world = game->getCurrentState()->getWorld();
}

GameObject::~GameObject() 
{
	for (auto it = _components.begin(); it != _components.end(); it++)
	{
		//No borra las Texturas porque de eso se encarga ~Game();
		if (it->first != "class Texture")
		{
			delete it->second;
			it->second = nullptr;
		}
	}
	_components.clear();

	//Llama a la destructora de los hijos
	for (GameObject* child : _children)
		delete child;

	_children.clear();
}

bool GameObject::handleEvent(const SDL_Event& event)
{
	for (InputComponent* ic : _inputComp)
		ic->handleEvent(event);

	//Llama al handleEvent de los hijos
	bool handled = false;
	auto it = _children.begin();
	while (!handled && it != _children.end())
	{
		if ((*it)->isActive())
			handled = (*it)->handleEvent(event);
		if(!handled) it++;
	}

	return handled;
}

void GameObject::update(double deltaTime)
{
	for (PhysicsComponent* pc : _physicsComp)
		pc->update(deltaTime);

	//Llama al update de los hijos
	for (GameObject* child : _children)
		if (child->isActive())
			child->update(deltaTime);
}

void GameObject::render(Camera* c) const
{
	for (RenderComponent* rc : _renderComp)
		rc->render(c);

	//Llama al render de los hijos
	for (GameObject* child : _children)
		if (child->isActive())
			child->render(c);
}

void GameObject::addInputComponent(InputComponent* ic)
{
	_inputComp.push_back(ic);
}

void GameObject::addPhysicsComponent(PhysicsComponent* pc)
{
	_physicsComp.push_back(pc);
}

void GameObject::addRenderComponent(RenderComponent* rc)
{
	_renderComp.push_back(rc);
}

void GameObject::delInputComponent(InputComponent* ic)
{
	std::vector<InputComponent*>::iterator position = std::find(_inputComp.begin(), _inputComp.end(), ic);

	if (position != _inputComp.end())
		_inputComp.erase(position);
}

void GameObject::delPhysicsComponent(PhysicsComponent* pc) {
	std::vector<PhysicsComponent*>::iterator position = std::find(_physicsComp.begin(), _physicsComp.end(), pc);

	if (position != _physicsComp.end())
		_physicsComp.erase(position);
}

void GameObject::delRenderComponent(RenderComponent* rc) {
	std::vector<RenderComponent*>::iterator position = std::find(_renderComp.begin(), _renderComp.end(), rc);

	if (position != _renderComp.end())
		_renderComp.erase(position);
}

void GameObject::destroyAllChildren()
{
	for(GameObject* child : _children)
		_game->getCurrentState()->destroyObject(child);
	_children.clear();
}

inline Camera * GameObject::getCamera() const
{
	return _game->getCurrentState()->getMainCamera();
}

Vector2D GameObject::getPositionOnCamera()
{
	auto transform = getComponent<TransformComponent>();
	auto mainCamera = _game->getCurrentState()->getMainCamera();

	//Cogemos su posicion en el mundo
	int xPos = transform->getPosition().getX();	int yPos = transform->getPosition().getY();

	//Lo convertimos en su posicion en camara
	xPos -= mainCamera->getCameraPosition().getX();
	yPos -= mainCamera->getCameraPosition().getY();

	double x = xPos * (CAMERA_RESOLUTION_X / _game->getCurrentState()->getMainCamera()->getCameraSize().getX());
	double y = yPos * (CAMERA_RESOLUTION_Y / _game->getCurrentState()->getMainCamera()->getCameraSize().getY());

	return Vector2D(x, y);
}

void GameObject::destroy()
{
	if (_game->getCurrentState() != nullptr) {
		_game->getCurrentState()->destroyObject(this);
	}
}
