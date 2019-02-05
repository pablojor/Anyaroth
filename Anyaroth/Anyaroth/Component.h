#pragma once

class GameComponent;

class Component {
protected:
	GameComponent* parent = nullptr;
public:
	Component(GameComponent* _parent);
	virtual ~Component();
};

