#pragma once
#include "PoolWrapper.h"
#include "Camera.h"

template<typename T, int SIZE>
class ObjectPool : public PoolWrapper
{
public:
	ObjectPool()
	{
		for (int i = 0; i < SIZE; i++)
			_objects[i].setActive(false);
	};

	ObjectPool(Game* g)
	{
		for (int i = 0; i < SIZE; i++)
		{
			_objects[i].setActive(false);
			_objects[i].setWorld(g->getWorld());
		}
	};

	virtual ~ObjectPool() {}

	virtual void update(double time);
	virtual void render(Camera* c) const;
	virtual void addBullet(Vector2D pos, Vector2D dir, double angle) {}

protected:
	T* getUnusedObject() 
	{
		for (int i = 0; i < SIZE; i++)
			if (!_objects[i].isActive())
				return &_objects[i];

		return nullptr;
	}

	//Coge el objeto _objects[i]
	T* getObject(int i)
	{
		return &_objects[i];
	}

	T _objects[SIZE];
};

template <typename T, int SIZE>
void ObjectPool<T, SIZE>::update(double time)
{
	for (int i = 0; i < SIZE; i++)
		if (_objects[i].isActive())
			_objects[i].update(time);
}

template <typename T, int SIZE>
void ObjectPool<T, SIZE>::render(Camera* c) const
{
	for (int i = 0; i < SIZE; i++)
		if (_objects[i].isActive())
			_objects[i].render(c);
}