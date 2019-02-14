#pragma once
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "Texture.h"

class GameComponent;

class FrameComponent : public RenderComponent
{
	private:
		Texture * _texture = nullptr;
		TransformComponent* _transform = nullptr;
		BodyComponent* _body = nullptr;
		bool _flip = false;
		int _fil = 1, _col = 1;

	public:
		FrameComponent(GameComponent* obj);
		virtual ~FrameComponent() {}

		virtual void render() const;
		void setFilAndCol(int fil, int col);
		void flip();
		void unFlip();
};