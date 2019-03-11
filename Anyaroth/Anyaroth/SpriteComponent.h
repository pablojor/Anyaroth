#pragma once
#include "RenderComponent.h"
#include "Texture.h"
#include "TransformComponent.h"

class GameComponent;

class SpriteComponent : public virtual RenderComponent
{
protected:
	Texture* _texture = nullptr;
	TransformComponent* _transform = nullptr;
	bool _flip = false;

public:
	SpriteComponent(GameComponent* obj);
	~SpriteComponent() {}

	virtual void render(Camera* c) const;
	void flip();
	void unFlip();
	inline bool isFlipped() { return _flip; };

	inline Texture* getTexture() const { return _texture; };
	inline void setTexture(Texture* texture) { _texture = texture; };
};