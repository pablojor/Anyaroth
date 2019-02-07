#pragma once
#include "RenderComponent.h"
#include "GameComponent.h"
#include "TransformComponent.h"

class SpriteComponent : public RenderComponent 
{
	private:
		Texture * _texture = nullptr;
		TransformComponent* _transform = nullptr;

		bool _flip = false;

	public:
		SpriteComponent(TransformComponent* trans, Texture* text) :
			_texture(text), _transform(trans) {}
		~SpriteComponent() {}
		void render() const;
		void flip();
		void unFlip();
};
