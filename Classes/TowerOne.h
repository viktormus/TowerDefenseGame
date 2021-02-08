#pragma once

#include "BaseTower.h"

USING_NS_CC;

class TowerOne : public BaseTower {
public:
	void update(float dt);
	bool init(float posX, float posY);
	static TowerOne* createTowerOne(float posX, float posY);
	void Attack(BaseEnemy* enemyHit);

};

