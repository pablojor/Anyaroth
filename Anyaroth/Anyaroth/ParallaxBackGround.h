#pragma once
#include "ParallaxLayer.h"
#include "BackGround.h"
#include <list>

class ParallaxBackGround : public BackGround
{
private:
	list<ParallaxLayer*> _layers;

public:
	ParallaxBackGround(Camera* camera) : BackGround(nullptr, camera) {}
	~ParallaxBackGround();

	virtual void update(double deltaTime);
	virtual void render() const;

	inline void addLayer(ParallaxLayer* layer) { _layers.push_back(layer); }
	inline void removeLayer(ParallaxLayer* layer) { _layers.remove(layer); }
	void changeDirection(bool normalWay);

	virtual bool checkCameraStatus(pair<bool, int> status);
};