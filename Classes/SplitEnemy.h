#pragma once

#include "cocos2d.h"
#include "BaseEnemy.h"

USING_NS_CC;

class SplitEnemy : public BaseEnemy {
public:
	static SplitEnemy* create();
	virtual bool init() override;

	virtual void ReduceHitpoints(float dmg) override;
	void SplitInTwo();
	void SpawnEnemyOne(float x, float y);
	bool CheckLastPoint(float x, float y);
private:
	// Constructor private to make misuse of this class difficult.
	SplitEnemy() {}
	~SplitEnemy() {}
};

