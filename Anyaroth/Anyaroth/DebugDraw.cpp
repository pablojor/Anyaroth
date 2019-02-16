#include "DebugDraw.h"
#include "Game.h"
#include "Texture.h"

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	SDL_Rect poly;
	poly.x = vertices[0].x;
	poly.y = vertices[0].y;
	poly.w = (vertices[0].x - vertices[1].x) > 0 ? vertices[0].x - vertices[1].x : vertices[1].x - vertices[0].x;
	poly.h = (vertices[0].y - vertices[1].y) > 0 ? vertices[0].y - vertices[1].y : vertices[1].y - vertices[0].y;
	SDL_RenderFillRect(_renderer, &poly);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	SDL_Rect poly;
	if(vertices[0].x<vertices[2].x)
	poly.x = vertices[0].x*M_TO_PIXEL;
	else
		poly.x = vertices[2].x*M_TO_PIXEL;
	if(vertices[0].y<vertices[2].y)
	poly.y = vertices[0].y*M_TO_PIXEL;
	else
		poly.y = vertices[2].y*M_TO_PIXEL;
	poly.h = abs(vertices[0].y - vertices[2].y)*M_TO_PIXEL;
	poly.w = abs(vertices[0].x - vertices[2].x)*M_TO_PIXEL;
	//SDL_RenderDrawRect(_renderer, &poly);
	Texture t = Texture(_renderer, SPRITE_PATH + "Body.png");
	t.render(poly);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	bool a;
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	bool a;
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	bool a;
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
	bool a;
}

void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
	bool a;
}

void DebugDraw::DrawString(int x, int y, const char *string, ...)
{
	bool a;
}

void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& c)
{
	SDL_Rect poly;
	poly.x = aabb->upperBound.x;
	poly.y = aabb->upperBound.y;
	poly.w = aabb->GetExtents().x * 2;
	poly.h = aabb->GetExtents().y * 2;
	SDL_RenderFillRect(_renderer, &poly);
}

void DebugDraw::getRenderer(SDL_Renderer* renderer)
{
	_renderer = renderer;
}
