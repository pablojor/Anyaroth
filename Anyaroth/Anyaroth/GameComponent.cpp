#include "GameComponent.h"

GameComponent::GameComponent() :
		GameObject(), inputComp_(), physicsComp_(), renderComp_() {
}

GameComponent::~GameComponent() {
	delete transform;
}

void GameComponent::handleEvents(/*Uint32 time, const*/ SDL_Event& event) {
	for (InputComponent* ic : inputComp_) {
		ic->handleInput(this, 0/*time*/, event);
	}
}

void GameComponent::update(/*Uint32 time*/) {
	for (PhysicsComponent* pc : physicsComp_) {
		pc->update(this, 0/*time*/);
	}
}

void GameComponent::render(/*Uint32 time*/) const {
	for (RenderComponent* rc : renderComp_) {
		rc->render(/*this, time*/);
	}
}

void GameComponent::addInputComponent(InputComponent* ic) {
	inputComp_.push_back(ic);
}

void GameComponent::addPhysicsComponent(PhysicsComponent* pc) {
	physicsComp_.push_back(pc);
}

void GameComponent::addRenderComponent(RenderComponent* rc) {
	renderComp_.push_back(rc);
}

void GameComponent::addComponent(Component* c) {
	extraComp_.push_back(c);
}

void GameComponent::delInputComponent(InputComponent* ic) {
	std::vector<InputComponent*>::iterator position = std::find(
			inputComp_.begin(), inputComp_.end(), ic);
	if (position != inputComp_.end())
		inputComp_.erase(position);
}

void GameComponent::delPhysicsComponent(PhysicsComponent* pc) {
	std::vector<PhysicsComponent*>::iterator position = std::find(
			physicsComp_.begin(), physicsComp_.end(), pc);
	if (position != physicsComp_.end())
		physicsComp_.erase(position);
}

void GameComponent::delRenderComponent(RenderComponent* rc) {
	std::vector<RenderComponent*>::iterator position = std::find(
			renderComp_.begin(), renderComp_.end(), rc);
	if (position != renderComp_.end())
		renderComp_.erase(position);
}

void GameComponent::delComponent(Component* c) {
	std::vector<Component*>::iterator position = std::find(
		extraComp_.begin(), extraComp_.end(), c);
	if (position != extraComp_.end())
		extraComp_.erase(position);
}
