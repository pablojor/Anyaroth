#pragma once
#include "RenderComponent.h"
#include "Texture.h"
#include "TransformComponent.h"

class SpriteComponent : public virtual RenderComponent
{
	protected:
		Texture* _texture = nullptr;
		TransformComponent* _transform = nullptr;

		bool _flip = false;
		bool _renderActive = true;

	public:
		SpriteComponent(GameObject* obj);
		~SpriteComponent() {}

		virtual void render(Camera* c) const;

		void flip();
		void unFlip();
		inline bool isFlipped() { return _flip; };

		inline Texture* getTexture() const { return _texture; };
		inline void setTexture(Texture* texture) { _texture = texture; };

		inline void setVisible(bool vis) { _renderActive = vis; };
};