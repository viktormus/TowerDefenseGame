#pragma once

#include "cocos2d.h"
#include "Wave.h"
#include "BaseTower.h"
#include <vector>


USING_NS_CC;

class GameManager {
public:
	static GameManager* GetInstance();

	void CreatePathTexture(Layer* layer);
	void Reset();

	// Stores Wave object so that it is easily accessible from here
	Wave* WaveObject;

	// Stores player money
	int Money = 150;

	// Stores all Enemies
	Vector<BaseEnemy*> Enemies;

	// Stores all towers
	Vector<BaseTower*> Towers;

	// Path points must be multiples of 50, because one tile texture is 50x50px
	std::vector<Point> Path { Point(100, 0), Point(100, 300), Point(600, 300), Point(600, 0) };
private:
	static GameManager* instance;
};

/*
* ADDITIONAL FEATURES:
Upgradeable towers(2 point) -- DONE
More different kinds of enemiesand towers(2 points) -- DONE
Tower placement can be altered during an enemy wave(2 points) -- DONE
Towers can be damaged by enemies(2 points) -- DONE
Sound effects(2 points) -- DONE
Different attackand defense types for both the towersand the enemies.For example, some attack types may be more effective against some defense types. (2 points) -- DONE
*/
// ALSO fix SplitEnemy so it spawns only two and prevent endpoint spawn... -- DONE


/* TO BE DONE
* -END SCREEN -- DONE
* -Balancing of game, game logic, cost of towers -- DONE
* -DEATH SCREEN -- DONE
* -Waves -- DONE
* */

// Towers Vector into GameManager, deletion and all management -- DONE
// Sidebar textures and functionality, clicking on regions, choosing proper texture -- DONE
// Additional enemy and tower textures -- DONE
// Tower that slows the enemy, NextMove implementation to change enemy speed immediately -- DONE
// Path texture, eg. 10x10px texture that is allocated properly with an algorithm -- DONE
// Bomb tower -- DONE
// Enemy that splits into multiple easier enemies -- DONE
// 5 Waves with increasing difficulty -- DONE
// Simple user interface that shows information such as resources, number of waves/enemies etc. - DONE