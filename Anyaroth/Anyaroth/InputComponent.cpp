#include "InputComponent.h"
#include "GameObject.h"

InputComponent::InputComponent(GameObject* obj) 
{
	obj->addInputComponent(this);
}