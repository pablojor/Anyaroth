#pragma once
#include "GameObject.h"
#include "TransformComponent.h"
#include "BodyComponent.h"

#include <functional>

class Game;

class Trigger :	public GameObject
{
private:
	TransformComponent* _transform = nullptr;
	BodyComponent* _body = nullptr;

	uint16 _collidesWith;
	bool _triggered = false;

	function<void()> _onTriggerEnter = nullptr;
	function<void()> _onTriggerExit = nullptr;
	function<void()> _onTriggerUpdate = nullptr;

public:
	Trigger(Game* game, int xPos = 0, int yPos = 0);
	~Trigger();

	virtual void update(double deltaTime);

	void beginCollision(GameObject* other, b2Contact* contact);
	void endCollision(GameObject* other, b2Contact* contact);

	//Funcion que se activa cuando entras al trigger
	void onTriggerEnter(function<void()> func);
	//Funcion que se activa cuando sales del trigger
	void onTriggerExit(function<void()> func);
	//Funcion que se activa cada ciclo de update() mientras estás dentro del trigger
	void onTriggerUpdate(function<void()> func);

	void setPosition(int xPos, int yPos);
	void setCollisionFilters(uint16 collidesWith);

	TransformComponent* getTransform() { return _transform; }
	BodyComponent* getBody() { return _body; }
};

