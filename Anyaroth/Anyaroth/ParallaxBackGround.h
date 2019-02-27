#pragma once
#include "ParallaxLayer.h"
#include "BackGround.h"
#include <vector>

class ParallaxBackGround : public BackGround
{
	private:
		vector<ParallaxLayer*> _layers;

	public:
		ParallaxBackGround(Camera* camera) : BackGround(nullptr, camera) {};
		~ParallaxBackGround();

		virtual void update();
		virtual void render() const;

		inline void addLayer(ParallaxLayer* layer) { _layers.push_back(layer); }
		void changeDirection(bool normalWay);
};

