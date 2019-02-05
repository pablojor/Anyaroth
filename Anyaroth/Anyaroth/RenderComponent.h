#ifndef RENDERCOMPONENT_H_
#define RENDERCOMPONENT_H_

#include "Component.h"

/*
 *
 */
class RenderComponent : public Component {
public:
	RenderComponent(GameComponent* parent);
	virtual ~RenderComponent();
	virtual void render(/*GameComponent* o, Uint32 time*/) const = 0;
};

#endif /* RENDERCOMPONENT_H_ */
