#include "SplitEnemy.h"

#include "GameManager.h"
#include "UserInterface.h"
#include <iostream>
#include <string>
#include <algorithm>

USING_NS_CC;


// Must use this instead of just calling the default constructor. This helps to manage memory!
SplitEnemy* SplitEnemy::create() {
    //Ulos("Inside EnemyOne::create");
    SplitEnemy* monster = new SplitEnemy();
    if (monster) {
        if (monster->init()) {
            monster->NextMove();
            monster->autorelease();
            return monster;
        }
    }
    CC_SAFE_DELETE(monster);
    return nullptr;
}

// This initializes the values to the Object, and may call other functions if needed
bool SplitEnemy::init() {
    //Ulos("Inside EnemyOne::init (ie. enemyOne has been created)");

    if (!Sprite::init()) {
        return false;
    }
    name_ = "SplitEnemy";
    hitpoints_ = 4;
    speed_ = 100;
    reward_ = 5;
    type_ = Evolved;

    baseSprite = Sprite::create("SplitEnemy.png");

    // This enemy always spawns at the first path point
    baseSprite->setPosition(Vec2(GameManager::GetInstance()->Path.at(0).x, GameManager::GetInstance()->Path.at(0).y));
    addChild(baseSprite);

    //Ulos("End of EnemyOne::init");
    return true;
}

void SplitEnemy::ReduceHitpoints(float dmg) {
    SoundManager::PlayShoot();
    hitpoints_ -= dmg;
    if (hitpoints_ <= 0) {
        //Ulos("The enemy has been killed.");
        GameManager::GetInstance()->Money += reward_;

        // Update money text
        std::string number = std::to_string(GameManager::GetInstance()->Money);
        UserInterface::GetInstance()->MoneyText->setString(number);

        SplitInTwo();       
        onDeath();
    }
}

void SplitEnemy::SplitInTwo() {

    float posX = baseSprite->getPosition().x;
    float posY = baseSprite->getPosition().y;

    // Checking whether new enemies should be spawned horizontally or vertically away from SplitEnemy (so that it stays on the path)
    if (posY == nextPoint.y) {

        // Without this, it wouldn't work when nextPoint.x has a smaller value
        if (nextPoint.x < prevProperPoint.x) {
            Point temp = prevProperPoint;
            prevProperPoint = nextPoint;
            nextPoint = temp;
        }

        // Checking that the spawn position is within the path coordinates
        if (nextPoint.x > posX + 17) {
            posX += 17;
        }
        else {
            posX = nextPoint.x;
        }

        if (CheckLastPoint(posX, posY)) {
            return;
        }
        SpawnEnemyOne(posX, posY);

        // Reset posX
        posX = baseSprite->getPosition().x;

        // Checking that the spawn position is within the path coordinates
        if (prevProperPoint.x < posX - 17) {
            posX -= 17;
        }
        else {
            posX = prevProperPoint.x;
        }

        if (CheckLastPoint(posX, posY)) {
            return;
        }
        SpawnEnemyOne(posX, posY);
    }

    else {

        // Reset posX
        posX = baseSprite->getPosition().x;

        // Without this, it wouldn't work when nextPoint.y has a smaller value
        if (nextPoint.y < prevProperPoint.y) {
            Point temp = prevProperPoint;
            prevProperPoint = nextPoint;
            nextPoint = temp;
        }

        // Checking that the spawn position is within the path coordinates
        if (nextPoint.y > posY + 17) {
            posY += 17;
        }
        else {
            posY = nextPoint.y;
        }

        if (CheckLastPoint(posX, posY)) {
            return;
        }
        SpawnEnemyOne(posX, posY);

        // Reset posY
        posY = baseSprite->getPosition().y;

        // Checking that the spawn position is within the path coordinates
        if (prevProperPoint.y < posY - 17) {
            posY -= 17;
        }
        else {
            posY = prevProperPoint.y;
        }

        if (CheckLastPoint(posX, posY)) {
            return;
        }
        SpawnEnemyOne(posX, posY);
    }
}

// For convenience in the function above
void SplitEnemy::SpawnEnemyOne(float x, float y) {
    EnemyOne* e = EnemyOne::create(x, y);
    GameManager::GetInstance()->WaveObject->addChild(e);
    GameManager::GetInstance()->Enemies.pushBack(e);
}

bool SplitEnemy::CheckLastPoint(float x, float y) {
    // Checking whether the enemy is going to be spawned at the last point of Path
    Point endP = GameManager::GetInstance()->Path.at(GameManager::GetInstance()->Path.size() - 1);
    if (x == endP.x && y == endP.y) {
        Ulos("spawnPoint = LastPoint");
        GameManager::GetInstance()->WaveObject->EndGame("lose");
        return true;
    }
    else {
        return false;
    }
}