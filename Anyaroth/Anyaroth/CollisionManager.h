#pragma once
#include <list>
#include <vector>
#include "Box2D/Box2D.h"

class CollisionManager : public b2ContactListener
{
public:
	virtual ~CollisionManager() {}
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact);
	void PostSolve(b2Contact* contact);
};