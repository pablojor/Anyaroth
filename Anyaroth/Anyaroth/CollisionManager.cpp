#include "CollisionManager.h"
#include "GameObject.h"

void CollisionManager::BeginContact(b2Contact * contact)
{
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	if (bodyUserDataA && bodyUserDataB)
	{
		GameObject* A = static_cast<GameObject*>(bodyUserDataA);
		GameObject* B = static_cast<GameObject*>(bodyUserDataB);
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
		GameObject* A = static_cast<GameObject*>(bodyUserDataA);
		GameObject* B = static_cast<GameObject*>(bodyUserDataB);
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
		GameObject* A = static_cast<GameObject*>(bodyUserDataA);
		GameObject* B = static_cast<GameObject*>(bodyUserDataB);
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
		GameObject* A = static_cast<GameObject*>(bodyUserDataA);
		GameObject* B = static_cast<GameObject*>(bodyUserDataB);
		A->postCollision(B, contact);
		B->postCollision(A, contact);
	}
}