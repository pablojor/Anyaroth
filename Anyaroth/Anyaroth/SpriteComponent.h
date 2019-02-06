#pragma once
#include "RenderComponent.h"
#include "GameComponent.h"
#include "TransformComponent.h"

class SpriteComponent : public RenderComponent 
{
	private:
		TextureComponent * _texture = nullptr;
		TransformComponent* _transform;
		bool _flip = false;

	public:
		SpriteComponent(TransformComponent* trans, TextureComponent* _texture);
		~SpriteComponent();
		void render() const;
		void flip();
		void unFlip();
};
