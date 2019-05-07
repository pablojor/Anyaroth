#pragma once
#include "PanelUI.h"
#include "LifeBar.h"
#include "TextUI.h"

class Enemy;

class EnemyLifePanel :	public PanelUI
{
private:
	ImageUI* _frame = nullptr;
	LifeBar* _lifeBar = nullptr;
	list<Enemy*> _enemies;

	void checkEnemyState(Enemy* enemy) const;

public:
	EnemyLifePanel(Game* game);
	~EnemyLifePanel();
	void updateLifeBar(int life1, int maxLife);

	virtual void render() const;

	inline void addEnemy(Enemy* enemy) { _enemies.push_back(enemy); };
	inline void removeEnemy(Enemy* enemy) { _enemies.remove(enemy); }
	inline void reset() { _enemies.clear(); }
};

