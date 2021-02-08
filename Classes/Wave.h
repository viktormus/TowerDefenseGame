#pragma once

#include "cocos2d.h"
#include "AudioEngine.h"
#include "EnemyOne.h"
#include "SplitEnemy.h"
#include "EnemyGreen.h"
#include "EnemyYellow.h"
#include "ArmoredEnemy.h"
#include "Ulos.h"
#include <algorithm> 
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <utility>

USING_NS_CC;

class Wave : public Layer {
public:
    static Scene* createScene();

    // Object creator with automatic memory management. Use by calling Wave::create();
    CREATE_FUNC(Wave);

    // Part of the function above. Must be used in all classes.
    virtual bool init();

    void WaveEvent(int number);
    void AddEnemy(float dt);
    int GetChosenTower();
    void EndGame(std::string condition);
    void update(float dt);

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    float curX, curY;

    // Counts the current wave number
    int waveN_;

    // If the Armored enemy attacks moving tower, it is set false and the tower object is deleted (throws an out of bounds vector exception without this)
    bool isMovable = true;

    // Song ID's for control
    int menuTheme_;
    int waveTheme_ = 1000;
    
private:
    std::vector<BaseEnemy*> enemiesInWave_;
    Vector<BaseEnemy*> newEnemies_;

    // Counts spawned enemies within current wave
    int enemyN_;

    // Automated wave size calculator
    void GetWaveL(std::vector<std::vector<int>>& vectorInput, std::vector<int>& otherV) {

        int size = vectorInput.size();

        for (int i = 0; i < size; i++) {
            size_t tempSize = vectorInput[i].size();
            for (unsigned int j = 1; j < tempSize; j += 2) {
                if (j < vectorInput[i].size()) {
                    //incrementing values of inputvector + 1 to SizeV vector (waveSize)
                    otherV[i] += vectorInput[i][j] + 1;
                }
            }
            //decrementing value by 1
            otherV[i] -= 1;
        }
    }
   
    // Wave contents are split into different waves, where
    // even integer tells us the enemy, and odd tells how many times it is spawned (starting from 0) in that order!
    // Eg. {EnemyOne, x2, EnemyGreen, x5, ...}
    // 0 = EnemyGreen
    // 1 = EnemyYellow
    // 2 = EnemyOne
    // 3 = ArmoredEnemy
    // 4 = SplitEnemy
    std::vector<std::vector<int>> waveContents_{
        {2,2},
        {2,1,0,3,4,0},
        {1,4,4,3}, 
        {2,4,1,2,0,3},
        {0, 4, 4, 4}, 
        {0,5,1,5,2,5,4,5,3,0},
        {2,10,3,3,1,10,3,5,4,20,3,10}

    };

    int nofWaves_ = waveContents_.size();

    std::vector<int> waveSize_ = std::vector<int>(nofWaves_, 0);

    // Tells us which enemy we should be spawning right now
    int waveSection_;

    // Tells us how many enemies of particular type have been spawned. Updates waveSection_
    int tempCount_;
    
    Scene* scenes;
    // Stores the vector index of the tower that is clicked
    int chosenTower;

    // Checks whether user moves the tower, so it doesn't open tower buttons
    bool towerMoved = false;
};