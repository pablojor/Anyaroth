#include "GameComponent.h"

GameComponent::GameComponent() :
		GameObject(), _inputComp(), _physicsComp(), _renderComp() {
}

GameComponent::~GameComponent() {
	for (RenderComponent* rc : _renderComp) delete rc;
	for (PhysicsComponent* pc : _physicsComp) delete pc;
	for (InputComponent* ic : _inputComp) delete ic;
	delete _transform;
}

void GameComponent::handleEvents(/*Uint32 time, const*/ SDL_Event& event) {
	for (InputComponent* ic : _inputComp) {
		ic->handleInput(this, 0/*time*/, event);
	}
}

void GameComponent::update(/*Uint32 time*/) {
	for (PhysicsComponent* pc : _physicsComp) {
		pc->update(/*this, 0*//*time*/);
	}
}

void GameComponent::render(/*Uint32 time*/) const {
	for (RenderComponent* rc : _renderComp) {
		rc->render(/*this, time*/);
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
	if (position != _inputComp.end()) {
		_inputComp.erase(position);
		delete ic;
	}
}

void GameComponent::delPhysicsComponent(PhysicsComponent* pc) {
	std::vector<PhysicsComponent*>::iterator position = std::find(
			_physicsComp.begin(), _physicsComp.end(), pc);
	if (position != _physicsComp.end()) {
		_physicsComp.erase(position);
		delete pc;
	}
}

void GameComponent::delRenderComponent(RenderComponent* rc) {
	std::vector<RenderComponent*>::iterator position = std::find(
			_renderComp.begin(), _renderComp.end(), rc);
	if (position != _renderComp.end()) {
		_renderComp.erase(position);
		delete rc;
	}
}

