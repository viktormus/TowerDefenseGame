#pragma once

#include "GameEngine.h"

#include <string>
#include <iostream>
#include <sstream>


void GameEngine::Run(cocos2d::Scene* scene) {

    // The reason I created a Wave object, instead of using static member functions and static member variables,
    // is because I couldn't push_back() anything to a static vector variable (it couldn't compile)
    //auto testWave = Wave::create();
    
    //testWave->WaveStart(scene);

    Ulos("");
    Ulos("---");
    Ulos("");
}