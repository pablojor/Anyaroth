#include "CollisionManager.h"
#include "GameComponent.h"

CollisionManager::~CollisionManager()
{
}


void CollisionManager::BeginContact(b2Contact * contact)
{
	cout << "colision" << endl;
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserDataA && bodyUserDataB)
	{
		GameComponent* A = static_cast<GameComponent*>(bodyUserDataA);
		GameComponent* B = static_cast<GameComponent*>(bodyUserDataB);
		A->beginCollision(B);
		B->beginCollision(A);
	}
	
}

void CollisionManager::EndContact(b2Contact * contact)
{
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserDataA && bodyUserDataB)
	{
		GameComponent* A = static_cast<GameComponent*>(bodyUserDataA);
		GameComponent* B = static_cast<GameComponent*>(bodyUserDataB);
		A->endCollision(B);
		B->endCollision(A);
	}
}

inline void CollisionManager::PreSolve(b2Contact * contact)
{
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserDataA && bodyUserDataB)
	{
		GameComponent* A = static_cast<GameComponent*>(bodyUserDataA);
		GameComponent* B = static_cast<GameComponent*>(bodyUserDataB);
		A->preCollision(B);
		B->preCollision(A);
	}
}

inline void CollisionManager::PostSolve(b2Contact * contact)
{
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserDataA && bodyUserDataB)
	{
		GameComponent* A = static_cast<GameComponent*>(bodyUserDataA);
		GameComponent* B = static_cast<GameComponent*>(bodyUserDataB);
		A->postCollision(B);
		B->postCollision(A);
	}
}
