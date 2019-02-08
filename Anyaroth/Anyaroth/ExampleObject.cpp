#include "ExampleObject.h"
#include "SpriteComponent.h"
#include "MovingComponent.h"
#include "PlayerControllerComponent.h"



ExampleObject::ExampleObject(Texture* texture) : GameComponent() {
	//Siempre primero los componentes que tienen que estar SI o SI.
	addComponent<Texture>(texture);
	//Resto de componentes
	addComponent<SpriteComponent>();	//Como depende de Transform, en su constructura crea una si no ha encontrado Transform en el objeto.
	addComponent<TransformComponent>();	//Como en el metodo anterior se ha creado este componente, imprime por pantalla que ya existe uno.

	//MovingComponent* a = new MovingComponent(transform, 0, 0);

	//addPhysicsComponent(a);
	//addInputComponent(new PlayerControllerComponent(a));

	auto transform = getComponent<TransformComponent>();

	transform->setScale(10);
	//transform->setPosition(720 / 2, 480 / 2);
	transform->setAnchor(0.5, 0.5);
	transform->setRotation(45);	
}

ExampleObject::~ExampleObject() {
}

void ExampleObject::update() {
	GameComponent::update();

	//transform->setRotation(transform->getRotation() + 0.2);
}
