#include "CollisionManager.h"
#include "GameComponent.h"

CollisionManager::~CollisionManager()
{
}


void CollisionManager::BeginContact(b2Contact * contact)
{
	cout << "colision" << endl;
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserDataA && bodyUserDataB)
	{
		GameComponent* A = static_cast<GameComponent*>(bodyUserDataA);
		GameComponent* B = static_cast<GameComponent*>(bodyUserDataB);
		A->beginCollision(B, contact);
		B->beginCollision(A, contact);
	}
}

void CollisionManager::EndContact(b2Contact * contact)
{
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserDataA && bodyUserDataB)
	{
		GameComponent* A = static_cast<GameComponent*>(bodyUserDataA);
		GameComponent* B = static_cast<GameComponent*>(bodyUserDataB);
		A->endCollision(B, contact);
		B->endCollision(A, contact);
	}
}

inline void CollisionManager::PreSolve(b2Contact * contact)
{
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserDataA && bodyUserDataB)
	{
		GameComponent* A = static_cast<GameComponent*>(bodyUserDataA);
		GameComponent* B = static_cast<GameComponent*>(bodyUserDataB);
		A->preCollision(B, contact);
		B->preCollision(A, contact);
	}
}

inline void CollisionManager::PostSolve(b2Contact * contact)
{
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserDataA && bodyUserDataB)
	{
		GameComponent* A = static_cast<GameComponent*>(bodyUserDataA);
		GameComponent* B = static_cast<GameComponent*>(bodyUserDataB);
		A->postCollision(B, contact);
		B->postCollision(A, contact);
	}
}