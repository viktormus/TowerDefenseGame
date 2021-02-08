#pragma once

#include "cocos2d.h"
#include "BaseTower.h"
#include "Ulos.h"

USING_NS_CC;

class SlowTower : public BaseTower {
public:
	void update(float dt);
	bool init(float posX, float posY);
	static SlowTower* createSlowTower(float posX, float posY);
	virtual float CompareTypes(BaseEnemy* enemy) override;
	virtual void EnemyCheck(float dt) override;
	void Attack(BaseEnemy* enemyHit) ;
	virtual void UpgradeTower() override;
private:
	float slow_;
	SlowTower() {}
	~SlowTower() {}
};

