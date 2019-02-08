#pragma once
#include "RenderComponent.h"
#include "GameComponent.h"
#include "TransformComponent.h"

class SpriteComponent : public RenderComponent 
{
	protected:
		Texture * _texture = nullptr;
		TransformComponent* _transform;
		bool _flip = false;

	public:
		SpriteComponent(TransformComponent* trans, Texture* _texture);
		~SpriteComponent();
		void render() const;
		void update() {};
		void flip();
		void unFlip();
};
