#include "InputComponent.h"
#include "GameComponent.h"


InputComponent::InputComponent(GameComponent* obj) 
{
	obj->addInputComponent(this);
}

InputComponent::~InputComponent() 
{

}

