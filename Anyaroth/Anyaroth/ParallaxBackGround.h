#pragma once
#include "ParallaxLayer.h"
#include "BackGround.h"
#include <vector>

class ParallaxBackGround : public BackGround
{
private:
	vector<ParallaxLayer*> _layers;

public:
	ParallaxBackGround(Camera* camera) : BackGround(nullptr, camera) {}
	~ParallaxBackGround();

	virtual void update(const double& deltaTime);
	virtual void render() const;

	inline void addLayer(ParallaxLayer* layer) { _layers.push_back(layer); }
	void changeDirection(bool normalWay);

	virtual bool checkCameraStatus(pair<bool, int> status);
};