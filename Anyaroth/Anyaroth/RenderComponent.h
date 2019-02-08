#ifndef RENDERCOMPONENT_H_
#define RENDERCOMPONENT_H_

/*
 *
 */
class RenderComponent {
public:
	RenderComponent();
	virtual ~RenderComponent();
	virtual void render(/*GameComponent* o, Uint32 time*/) const = 0;
};

#endif /* RENDERCOMPONENT_H_ */
