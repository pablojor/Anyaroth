#pragma once
#include "Box2D/Box2D.h"
#include <SDL.h>
#include "Texture.h"
#include "Camera.h"

class DebugDraw : public b2Draw
{
private:
	SDL_Renderer* _renderer = nullptr;
	Texture* _texture = nullptr;
	Camera* _camera = nullptr;

public:
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	void DrawTransform(const b2Transform& xf);
	void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
	void DrawString(int x, int y, const char* string, ...);
	void DrawAABB(b2AABB* aabb, const b2Color& color);

	inline void getRenderer(SDL_Renderer* renderer) { _renderer = renderer; }
	inline void getTexture(Texture* t) { _texture = t; }
	inline void getCamera(Camera* c) { _camera = c; }
};