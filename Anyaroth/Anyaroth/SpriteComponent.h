#pragma once
#include "RenderComponent.h"
#include "Texture.h"
#include "TransformComponent.h"
#include "BodyComponent.h"

class GameComponent;

class SpriteComponent : public virtual RenderComponent
{
	protected:
		Texture * _texture = nullptr;
		TransformComponent* _transform = nullptr;
		BodyComponent* _body = nullptr;
		bool _flip = false;

	public:
		SpriteComponent(GameComponent* obj);
		~SpriteComponent() {}
		virtual void render() const;
		void flip();
		void unFlip();
};