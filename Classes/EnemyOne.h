#pragma once

#include "cocos2d.h"
#include "BaseEnemy.h"
#include "Ulos.h"
//#include "GameManager.h"

#include <string>

USING_NS_CC;

class EnemyOne : public BaseEnemy {
public:
	// Creator method that works as a constructor and has default values for this enemy type
	static EnemyOne* create(float posX = 0, float posY = 0);

	// Part of the create method, which won't work without this
	virtual bool init(float posX, float posY);

private:
	// Constructor private to make misuse of this class difficult.
	EnemyOne() {}
	~EnemyOne() {}
};

