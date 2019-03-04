#include "GameComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "InputComponent.h"
#include "Game.h"

GameComponent::GameComponent(Game* g, string tag) : _game(g), GameObject(), _inputComp(), _physicsComp(), _renderComp(), _tag(tag)
{
	_world = g->getWorld();
}

//Constructor vac�o (sin puntero a game, _game = nullptr)
GameComponent::GameComponent() : GameObject(), _inputComp(), _physicsComp(), _renderComp(), _tag() {}

GameComponent::~GameComponent() 
{
	/*for (RenderComponent* rc : renderComp_) delete rc;
	for (PhysicsComponent* pc : physicsComp_) delete pc;
	for (InputComponent* ic : inputComp_) delete ic;*/
	
	for (auto it = _components.begin(); it != _components.end(); it++)
	{
		//No borra las Texturas porque de eso se encarga ~Game();
		if (it->first != "class Texture")
		{
			delete it->second;
			it->second = nullptr;
		}
	}

	//Llama a la destructora de los hijos
	for (GameComponent* child : _children)
	{
		delete child;
	}
}

//A�ade un hijo al objeto
void GameComponent::addChild(GameComponent* obj) 
{
	_children.push_back(obj);
}

bool GameComponent::handleInput(const SDL_Event& event) 
{
	for (InputComponent* ic : _inputComp) 
	{
		ic->handleInput(event);
	}

	//Llama al handleInput de los hijos
	for (GameComponent* child : _children)
	{
		child->handleInput(event);
	}

	return false;
}

void GameComponent::update() 
{
	for (PhysicsComponent* pc : _physicsComp) 
	{
		pc->update();
	}

	//Llama al update de los hijos
	for (GameComponent* child : _children)
	{
		child->update();
	}
}

void GameComponent::render(Camera* c) const {
	for (RenderComponent* rc : _renderComp) {
		rc->render(c);
	}

	//Llama al render de los hijos
	for (GameComponent* child : _children)
	{
		child->render(c);
	}
}

void GameComponent::addInputComponent(InputComponent* ic) {
	_inputComp.push_back(ic);
}

void GameComponent::addPhysicsComponent(PhysicsComponent* pc) {
	_physicsComp.push_back(pc);
}

void GameComponent::addRenderComponent(RenderComponent* rc) {
	_renderComp.push_back(rc);
}

void GameComponent::delInputComponent(InputComponent* ic) {
	std::vector<InputComponent*>::iterator position = std::find(
			_inputComp.begin(), _inputComp.end(), ic);
	if (position != _inputComp.end())
		_inputComp.erase(position);
}

void GameComponent::delPhysicsComponent(PhysicsComponent* pc) {
	std::vector<PhysicsComponent*>::iterator position = std::find(
			_physicsComp.begin(), _physicsComp.end(), pc);
	if (position != _physicsComp.end())
		_physicsComp.erase(position);
}

void GameComponent::delRenderComponent(RenderComponent* rc) {
	std::vector<RenderComponent*>::iterator position = std::find(
			_renderComp.begin(), _renderComp.end(), rc);
	if (position != _renderComp.end())
		_renderComp.erase(position);
}

b2World * GameComponent::getWorld()
{
	return _world;
}