#pragma once

#include "cocos2d.h"
#include "Ulos.h"

class GameEngine {
public: 
	GameEngine() {}
	~GameEngine() {};

	// Note that static functions work without having to create an object of this class
	static void Run(cocos2d::Scene* scene);
};

