#pragma once
#include "RenderComponent.h"
#include "Texture.h"
#include "TransformComponent.h"
#include "Texture.h"

class GameComponent;

class SpriteComponent : public RenderComponent 
{
	private:
		Texture * _texture = nullptr;
		TransformComponent* _transform = nullptr;
		bool _flip = false;

	public:
		SpriteComponent(GameComponent* obj);
		~SpriteComponent();
		void render() const;
		void renderFrame(int fil, int col) const;
		void flip();
		void unFlip();
};
