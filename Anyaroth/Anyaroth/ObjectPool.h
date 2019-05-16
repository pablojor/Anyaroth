#pragma once
#include "PoolWrapper.h"
#include "Camera.h"
#include <vector>

template<typename T, int SIZE>
class ObjectPool : public PoolWrapper 
{
public:

	ObjectPool(Game* g) : PoolWrapper(g)
	{
		for (int i = 0; i < SIZE; i++) 
		{
			_objects.push_back(new T(g));
			_objects[i]->setActive(false);
			_objects[i]->setWorld(getWorld());
		}
	};

	virtual ~ObjectPool() 
	{
		for (T* t : _objects)
			delete t;
	};

	virtual void update(double deltaTime);
	virtual void render(Camera* c) const;
	virtual void addBullet(Vector2D pos, Vector2D dir, double angle) {}

	virtual void addObject(T* object) {	_objects.push_back(object); }

	//const int MAX_SIZE = SIZE;
	virtual T* getUnusedObject() 
	{
		for (int i = 0; i < _objects.size(); i++)
			if (!_objects[i]->isActive())
				return _objects[i];
		return nullptr;
	}

	//Coge el objeto _objects[i]
	virtual T* getObject(int i)
	{
		return _objects[i];
	}

	vector<T*> _objects;
};

template <typename T, int SIZE>
void ObjectPool<T, SIZE>::update(double deltaTime) 
{
	for (int i = 0; i < _objects.size(); i++)
		if (_objects[i]->isActive()) 
			_objects[i]->update(deltaTime);
}

template <typename T, int SIZE>
void ObjectPool<T, SIZE>::render(Camera* c) const 
{
	for (int i = 0; i < _objects.size(); i++)
		if (_objects[i]->isActive())
			_objects[i]->render(c);
}