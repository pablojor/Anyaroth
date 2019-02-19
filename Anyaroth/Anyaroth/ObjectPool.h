#pragma once
#include "GameObject.h"

template<typename T, int SIZE>
class ObjectPool : public GameComponent {
public:
	ObjectPool() : GameComponent() {
		for (int i = 0; i < SIZE; i++) {
			objects_[i].setActive(false);
		}
	};
	virtual ~ObjectPool() {};

	virtual void handleInput(const SDL_Event& event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	//virtual void addBullet(Vector2D pos, Vector2D vel);
protected:
	//const int MAX_SIZE = SIZE;
	T* getUnusedObject() {
		for (int i = 0; i < SIZE; i++)
			if (!objects_[i].isActive()) {
				return &objects_[i];
			}

		return nullptr;
	}

	T objects_[SIZE];
};


