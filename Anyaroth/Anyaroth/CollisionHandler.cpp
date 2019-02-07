#include "CollisionHandler.h"

bool CollisionHandler::AABBCollision(SDL_Rect rectA, SDL_Rect rectB)
{
	return (rectA.x + rectA.w >= rectB.x &&
			rectA.y + rectA.h >= rectB.y &&
			rectB.x + rectB.w >= rectA.x &&
			rectB.y + rectB.h >= rectA.y);
}