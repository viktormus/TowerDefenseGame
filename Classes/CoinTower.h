#pragma once

#include "cocos2d.h"
#include "BaseTower.h"

class CoinTower : public BaseTower {
public:
	void update(float dt);
	bool init(float posX, float posY);
	void Attack(BaseEnemy* enemyHit) ;
	static CoinTower* createCoinTower(float posX, float posY);
	virtual void UpgradeTower() override;
	virtual void EnemyCheck(float dt) override;
private:
	int rewardMult_;
	CoinTower() {}
	~CoinTower() {}
};

