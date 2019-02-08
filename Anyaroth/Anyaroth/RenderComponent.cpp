#include "RenderComponent.h"
#include "GameComponent.h"

RenderComponent::RenderComponent(GameComponent* obj) { obj->addRenderComponent(this); }

RenderComponent::~RenderComponent() {
	// TODO Auto-generated destructor stub
}

