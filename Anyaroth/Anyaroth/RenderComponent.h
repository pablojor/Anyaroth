#include "Component.h"

class GameComponent;

class RenderComponent : public virtual Component 
{
	public:
		RenderComponent(GameComponent* obj);
		virtual ~RenderComponent();
		virtual void render() const = 0;
};