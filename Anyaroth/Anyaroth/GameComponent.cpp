#include "GameComponent.h"

GameComponent::GameComponent() :
		GameObject(), inputComp_(), physicsComp_(), renderComp_() {
}

GameComponent::~GameComponent() {
	for (RenderComponent* rc : renderComp_) delete rc;
	for (PhysicsComponent* pc : physicsComp_) delete pc;
	for (InputComponent* ic : inputComp_) delete ic;
	delete transform;
}

void GameComponent::handleEvents(/*Uint32 time, const*/ SDL_Event& event) {
	for (InputComponent* ic : inputComp_) {
		ic->handleInput(/*this, 0time*/ event);
	}
}

void GameComponent::update(/*Uint32 time*/) {
	for (PhysicsComponent* pc : physicsComp_) {
		pc->update(/*this, 0*//*time*/);
		
	}

	
}

void GameComponent::render(/*Uint32 time*/) const {
	for (RenderComponent* rc : renderComp_) {
		rc->render(/*this, time*/);
		rc->update();
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

void GameComponent::delInputComponent(InputComponent* ic) {
	std::vector<InputComponent*>::iterator position = std::find(
			inputComp_.begin(), inputComp_.end(), ic);
	if (position != inputComp_.end()) {
		inputComp_.erase(position);
		delete ic;
	}
}

void GameComponent::delPhysicsComponent(PhysicsComponent* pc) {
	std::vector<PhysicsComponent*>::iterator position = std::find(
			physicsComp_.begin(), physicsComp_.end(), pc);
	if (position != physicsComp_.end()) {
		physicsComp_.erase(position);
		delete pc;
	}
}

void GameComponent::delRenderComponent(RenderComponent* rc) {
	std::vector<RenderComponent*>::iterator position = std::find(
			renderComp_.begin(), renderComp_.end(), rc);
	if (position != renderComp_.end()) {
		renderComp_.erase(position);
		delete rc;
	}
}

