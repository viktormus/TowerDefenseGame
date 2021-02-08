#pragma once

#include "ArmoredEnemy.h"
#include "GameManager.h"
#include <iostream>
#include <string>

USING_NS_CC;


// Must use this instead of just calling the default constructor. This helps to manage memory!
ArmoredEnemy* ArmoredEnemy::create(float posX, float posY) {
    //Ulos("Inside EnemyOne::create");
    ArmoredEnemy* monster = new ArmoredEnemy();
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
bool ArmoredEnemy::init(float posX, float posY) {
    //Ulos("Inside EnemyOne::init (ie. enemyOne has been created)");

    if (!Sprite::init()) {
        return false;
    }
    name_ = "ArmoredEnemy";
    hitpoints_ = 20;
    speed_ = 65;
    reward_ = 15;
    type_ = Armored;

    //Ulos("Variable testing X:", posX);
    //Ulos("Variable testing Y:", posY);

    baseSprite = Sprite::create("ArmoredEnemy.png");

    if (posX == 0 && posY == 0) {
        baseSprite->setPosition(Vec2(GameManager::GetInstance()->Path.at(0).x, GameManager::GetInstance()->Path.at(0).y));
    }
    else {
        baseSprite->setPosition(Vec2(posX, posY));
    }

    addChild(baseSprite);

    this->scheduleUpdate();
    return true;
}

// Checks for towers in proximity and destroys them (in one hit), after which can't attack anymore
void ArmoredEnemy::update(float dt) {
    Vector<BaseTower*> towers = GameManager::GetInstance()->Towers;

    for (int i = 0; i < towers.size(); i++) {
        BaseTower* tower = towers.at(i);
        float distance = baseSprite->getPosition().getDistance(tower->GetSprite()->getPosition());
        if (distance < 100) {
            
            GameManager::GetInstance()->WaveObject->isMovable = false;
            tower->unscheduleAllCallbacks();
            GameManager::GetInstance()->Towers.eraseObject(tower);
            tower->removeFromParent();

            unscheduleUpdate();
            break;
        }
    }
}