#pragma once
#include "RenderComponent.h"
#include "Texture.h"
#include "TransformComponent.h"

class GameComponent;

class SpriteComponent : public RenderComponent 
{
	protected:
		Texture * _texture = nullptr;
		TransformComponent* _transform = nullptr;
		bool _flip = false;

	public:
		SpriteComponent(GameComponent* obj);
		~SpriteComponent();
		void render() const;
		void flip();
		void unFlip();
};
