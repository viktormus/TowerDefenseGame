#pragma once

#include "cocos2d.h"
#include "BaseEnemy.h"
#include "BaseTower.h"

class ArmoredEnemy : public BaseEnemy {
public:
	static ArmoredEnemy* create(float posX = 0, float posY = 0);
	virtual bool init(float posX, float posY);
	void update(float dt);
private:
	// Constructor private to make misuse of this class difficult.
	ArmoredEnemy() {}
	~ArmoredEnemy() {}
};