#pragma once

#include "cocos2d.h"
#include "BaseTower.h"

class LightningTower : public BaseTower {
public:
	void update(float dt);
	bool init(float posX, float posY);
	void Attack(BaseEnemy* enemyHit);
	static LightningTower* createLightningTower(float posX, float posY);
private:
	LightningTower() {}
	~LightningTower() {}
};

