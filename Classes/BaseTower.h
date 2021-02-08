#pragma once

#include "cocos2d.h"
#include "Ulos.h"
#include "BaseEnemy.h"

#include "vector"
#include "CCVector.h"


USING_NS_CC;

class BaseTower : public Sprite {
public:
	BaseTower();
	~BaseTower() {}
	virtual bool init() override;

	virtual void EnemyCheck(float dt);
	virtual void Attack(BaseEnemy* enemyHit) = 0;
	virtual float CompareTypes(BaseEnemy* enemy);

	void SellTower();
	virtual void UpgradeTower();

	const std::string& GetName() const;
	float GetDamage();
	float GetRadius();
	float GetAS();
	Sprite* GetSprite() const;
	int GetPrice();
	bool isUpgraded();

protected:
	std::string name_;
	float hitpoints_;
	float damage_;
	float radius_;
	float attackSpeed_;
	int price_;
	Sprite* image_;
	bool firstHit_;
	bool upgraded_;
	Attribute strongAgainst_;
	Attribute weakAgainst_;
};

