#pragma once
#include "PoolWrapper.h"

template<typename T, int SIZE>
class ObjectPool : public PoolWrapper {
public:
	ObjectPool() : PoolWrapper() {
		for (int i = 0; i < SIZE; i++) {
			objects_[i].setActive(false);
		}
	};
	virtual ~ObjectPool() {};

	/*virtual void handleInput(const SDL_Event& event) = 0; //Ya están en GameObject
	virtual void update() = 0;
	virtual void render() = 0;*/

	virtual void addBullet(Vector2D pos, Vector2D dir) {};

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


