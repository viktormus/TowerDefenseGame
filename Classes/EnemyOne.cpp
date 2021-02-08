#pragma once

#include "EnemyOne.h"
#include "GameManager.h"
#include <iostream>
#include <string>

USING_NS_CC;


// Must use this instead of just calling the default constructor. This helps to manage memory!
EnemyOne* EnemyOne::create(float posX, float posY) {
    //Ulos("Inside EnemyOne::create");
    EnemyOne* monster = new EnemyOne();
    if (monster) {
        if (monster->init(posX, posY)) {
            monster->NextMove();
            monster->autorelease();
            return monster;
        }
    }
    CC_SAFE_DELETE(monster);
    return nullptr;
}

// This initializes the values to the Object, and may call other functions if needed
bool EnemyOne::init(float posX, float posY) {
    //Ulos("Inside EnemyOne::init (ie. enemyOne has been created)");

    if (!Sprite::init()) {
		return false;
	}

    name_ = "EnemyOne";
    hitpoints_ = 1;
    speed_ = 125;
    reward_ = 5;
    type_ = Fire;
    
    //Ulos("Variable testing X:", posX);
    //Ulos("Variable testing Y:", posY);

    baseSprite = Sprite::create("Enemy1.png");

    // Start at the 1st path point or else...
    if (posX == 0 && posY == 0) {
        baseSprite->setPosition(Vec2(GameManager::GetInstance()->Path.at(0).x, GameManager::GetInstance()->Path.at(0).y));
    }
    else {
        baseSprite->setPosition(Vec2(posX, posY));
    }
    
    addChild(baseSprite);

    //Ulos("End of EnemyOne::init");
	return true;
}