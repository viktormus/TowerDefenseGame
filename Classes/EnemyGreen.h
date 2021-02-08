#pragma once

#include "cocos2d.h"
#include "BaseEnemy.h"
#include "Ulos.h"
#include <string>

class EnemyGreen : public BaseEnemy {
public:
	static EnemyGreen* create(float posX = 0, float posY = 0);
	virtual bool init(float posX, float posY);
private:
	// Constructor private to make misuse of this class difficult.
	EnemyGreen() {}
	~EnemyGreen() {}
};

