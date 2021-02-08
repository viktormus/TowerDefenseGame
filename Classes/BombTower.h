#pragma once

#include "cocos2d.h"
#include "BaseTower.h"
#include "Ulos.h"

USING_NS_CC;

class BombTower : public BaseTower {
public:
	void update(float dt);
	bool init(float posX, float posY);
	static BombTower* createBombTower(float posX, float posY);
	virtual void Attack(BaseEnemy* enemyHit) override;
private:
	int bombRadius_;
	BombTower() {}
	~BombTower() {}
};

