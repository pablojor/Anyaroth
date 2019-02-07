#pragma once
#include "RenderComponent.h"
#include "GameComponent.h"
#include "TransformComponent.h"
#include "Texture.h"

class SpriteComponent : public RenderComponent 
{
	private:
		Texture * _texture = nullptr;
		TransformComponent* _transform;
		bool _flip = false;

	public:
		SpriteComponent(TransformComponent* trans, Texture* _texture);
		~SpriteComponent();
		void render() const;
		void renderFrame(int fil, int col) const;
		void flip();
		void unFlip();
};
