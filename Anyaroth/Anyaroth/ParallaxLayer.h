#pragma once
#include "Texture.h"
#include "BackGround.h"

class Camera;

class ParallaxLayer : public BackGround
{
private:
	int _speed = 2;	//De momento es la velocidad en pixeles
	bool _leftDir = true;

public:
	ParallaxLayer(Texture* texture, Camera* camera) : BackGround(texture, camera) {};
	~ParallaxLayer() {};

	virtual void render() const;
	virtual void update();

	inline void setSpeed(int s) { _speed = s; }
	inline int getSpeed() { return _speed; }
	inline void changeDir(bool leftDir) { _leftDir = leftDir; }
};

