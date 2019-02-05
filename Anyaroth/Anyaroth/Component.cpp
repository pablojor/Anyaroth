#include "Component.h"
#include "GameComponent.h"

Component::Component(GameComponent* _parent) {
	parent = _parent;
}

Component::~Component() {
	/*if (parent != nullptr)
		delete parent;*/
}
