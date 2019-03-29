#include "RenderComponent.h"
#include "GameObject.h"

RenderComponent::RenderComponent(GameObject* obj) 
{ 
	obj->addRenderComponent(this); 
}