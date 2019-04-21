#pragma once
#include "GameObject.h"
#include "TransformComponent.h"
#include "AnimatedSpriteComponent.h"
#include "BodyComponent.h"
#include "Player.h"

class Interactable : public GameObject
{
protected:
	//Componentes
	TransformComponent* _transform = nullptr;
	AnimatedSpriteComponent* _anim = nullptr;
	BodyComponent* _body = nullptr;
	Player* _other = nullptr;

	bool _canInteract = false;
	GameObject* _interactIndicator = nullptr;

	
public:
	Interactable(Game* g, Vector2D posIni);
	virtual ~Interactable();

	virtual void update(const double& time);
	virtual bool handleEvent(const SDL_Event& event);

	virtual void interact() {};

	void beginCollision(GameObject * other, b2Contact* contact);
	void endCollision(GameObject * other, b2Contact* contact);
};