#pragma once
#include "RenderComponent.h"
#include "Texture.h"
#include "TransformComponent.h"

class GameComponent;

class SpriteComponent : public virtual RenderComponent
{
	protected:
		Texture * _texture = nullptr;
		TransformComponent* _transform = nullptr;
		bool _flip = false;

	public:
		SpriteComponent(GameComponent* obj);
		~SpriteComponent() {}
		virtual void render() const;
		void flip();
		void unFlip();
		bool isFlipped() { return _flip; };

		Texture* getTexture() { return _texture; };
		void setTexture(Texture* texture) { _texture = texture; };
};