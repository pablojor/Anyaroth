#pragma once
#include "Texture.h"
#include "BackGround.h"

class Camera;

class ParallaxLayer : public BackGround
{
private:
	float _speed = 0.5;	//De momento es la velocidad en pixeles
	bool _leftDir = true;
	float _auxX = 0;

public:
	ParallaxLayer(Texture* texture, Camera* camera) : BackGround(texture, camera) {};
	ParallaxLayer(Texture* texture, Camera* camera, float speed) : BackGround(texture, camera), _speed(speed) {};
	~ParallaxLayer() {};

	virtual void render() const;
	virtual void update();

	inline void setSpeed(float s) { _speed = s; }
	inline float getSpeed() { return _speed; }
	inline void changeDir(bool leftDir) { _leftDir = leftDir; }
	
	inline bool checkCameraStatus(pair<bool, int> status) { return true; }
};

