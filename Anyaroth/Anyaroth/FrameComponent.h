#pragma once
#include "RenderComponent.h"
#include "TransformComponent.h"

class FrameComponent : public RenderComponent
{
private:
	Texture * _texture = nullptr;
	TransformComponent* _transform;
	bool _flip = false;
	int fil, col;

public:
	FrameComponent(TransformComponent* trans, Texture* _texture, int fil, int col);
	~FrameComponent();
	virtual void render() const;
	void flip();
	void unFlip();
};
