#pragma once

#include <list>
#include <vector>
#include <Box2D/Box2D.h>

class CollisionManager : public b2ContactListener
{
	public:
		void beginContact(b2Contact* contact);
		void endContact(b2Contact* contact);
		void preSolve(b2Contact* contact);
		void postSolve(b2Contact* contact);
		
};
