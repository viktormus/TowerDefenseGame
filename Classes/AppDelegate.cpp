#pragma once

#include "AppDelegate.h"
#include "Wave.h"
#include "TowerOne.h"
#include <iostream>
#include <string>


USING_NS_CC;

AppDelegate::AppDelegate() {
}
AppDelegate::~AppDelegate()
{
}
bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
        glview = GLViewImpl::create("Tower Defense");
        glview->setFrameSize(960, 640);
        director->setOpenGLView(glview);
    }
    
    //Ulos("Application is running...");
    auto scene = Wave::createScene();
    director->runWithScene(scene);
    
    return true;
}
void AppDelegate::applicationDidEnterBackground() {
}
void AppDelegate::applicationWillEnterForeground() {
}