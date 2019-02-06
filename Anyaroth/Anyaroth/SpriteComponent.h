#pragma once
#include "RenderComponent.h"
#include "GameComponent.h"
#include "TransformComponent.h"

class SpriteComponent : public RenderComponent {
private:
	TextureComponent * texture = nullptr;
	unsigned int width = 0;
	unsigned int heigth = 0;
	TransformComponent* transform;
public:
	SpriteComponent(TransformComponent* trans, TextureComponent* _texture, unsigned int _width, unsigned int _heigth);
	~SpriteComponent();
	void render() const;
};
