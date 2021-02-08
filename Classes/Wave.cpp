#pragma once

#include "Wave.h"
#include "GameManager.h"
#include "ui/CocosGUI.h"
#include "UserInterface.h"
#include "AddTowerLayer.h"

USING_NS_CC;

Scene* Wave::createScene() {

    // Setup for UI and new game

    // 'scene' is an autorelease object
    auto scene = Scene::create();
    auto layer = Wave::create();
    scene->addChild(layer);


    GameManager::GetInstance()->Reset();
    GameManager::GetInstance()->WaveObject = layer;

    auto bg = Sprite::create("Background.png");
    bg->setAnchorPoint(Vec2(0, 0));
    layer->addChild(bg);
    auto ok = AddTowerLayer::create();
    
    UserInterface::GetInstance()->CreateStartWaveButton(layer);
    UserInterface::GetInstance()->CreateSellTowerButton(layer);
    UserInterface::GetInstance()->SellTowerButton->setEnabled(false);
    UserInterface::GetInstance()->SellTowerButton->setVisible(false);
    UserInterface::GetInstance()->CreateUpgradeTowerButton(layer);
    GameManager::GetInstance()->CreatePathTexture(layer);
    UserInterface::GetInstance()->CreateMoneyText(layer);
    UserInterface::GetInstance()->CreateRoundText(layer);
    
    return scene;
}

bool Wave::init() {
    if (!Layer::init())
    {
        return false;
    }

    // Following mouse activity
    auto listener = EventListenerTouchOneByOne::create();
    //listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(Wave::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Wave::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Wave::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    waveN_ = 0;
    enemyN_ = -1;
    waveSection_ = 0;
    tempCount_ = -1;
    GetWaveL(waveContents_, waveSize_);

    menuTheme_ = SoundManager::PlayMenuTheme();
    //Ulos("menuTheme_:", menuTheme_);
    
    this->scheduleUpdate();
    return true;
}

// parent chain of visible textures
// scene->addChild(layer->addChild(sprite = texture file));

void Wave::WaveEvent(int number) {
    //Ulos("in WaveEvent");
    //Ulos("number argument:", number);
    UserInterface::GetInstance()->StartWaveButton->setEnabled(false);
    schedule(SEL_SCHEDULE(&Wave::AddEnemy), 0.5, waveSize_[number], 0);
}

void Wave::AddEnemy(float dt) {
    
    // Check whether we have spawned particular enemy type as many times as we had to
    if (waveContents_[waveN_][waveSection_ + 1] == tempCount_) {
        waveSection_ += 2;
        tempCount_ = -1;
    }

    BaseEnemy* enemy;
    switch (waveContents_[waveN_][waveSection_]) {
    case 0:
        enemy = EnemyGreen::create();
        break;
    case 1:
        enemy = EnemyYellow::create();
        break;
    case 2:
        enemy = EnemyOne::create();
        break;
    case 3:
        enemy = ArmoredEnemy::create();
        break;
    case 4:
        enemy = SplitEnemy::create();
        break;
    }
    
    enemyN_++;
    //Ulos("enemyN_", enemyN_);
    tempCount_++;

    this->addChild(enemy);
    //Ulos("In AddEnemy before pushing created enemy into Enemies vector");
    GameManager::GetInstance()->Enemies.pushBack(enemy);
}

bool Wave::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    isMovable = true;
    chosenTower = -1;
    if (touch->getLocation().x < 700) {
        curX = touch->getLocation().x;
        curY = touch->getLocation().y;
        //CCLOG("onTouchBegan: Location is x= %f, y=%f", touch->getLocation().x, touch->getLocation().y);

        if (GameManager::GetInstance()->Towers.size() > 0) {
            for (int i = 0; i < GameManager::GetInstance()->Towers.size(); i++) {
                if (GameManager::GetInstance()->Towers.at(i)->GetSprite()->getBoundingBox().containsPoint(touch->getLocation())) {
                    chosenTower = i;
                    //Ulos("YOU CLICKED THE TOWER NUMBER #", i);
                    break;
                }
            }
        }
        return 1;
    }
    return 0;
}

void Wave::onTouchMoved(Touch* touch, Event* event) {
    curX = touch->getLocation().x;
    curY = touch->getLocation().y;

    UserInterface::GetInstance()->SellTowerButton->setVisible(false);
    UserInterface::GetInstance()->SellTowerButton->setEnabled(false);
    UserInterface::GetInstance()->UpgradeTowerButton->setVisible(false);
    UserInterface::GetInstance()->UpgradeTowerButton->setEnabled(false);

    // Keeping the towers withing screen frame
    if (chosenTower != -1) {
        if (curX > 680) {
            curX = 680;
        } else if (curX < 30) {
            curX = 30;
        }
        if (curY > 525) {
            curY = 525;
        } else if (curY < 43) {
            curY = 43;
        }

        // This throws an out of bounds error if enemies kill the tower in the midst of moving process -> skipped if enemy attacks tower
        if (isMovable) {
            GameManager::GetInstance()->Towers.at(chosenTower)->GetSprite()->setPosition(curX, curY);
        }
        towerMoved = true;
    }
    //CCLOG("onTouchMoved: Location is x= %f, y=%f", touch->getLocation().x, touch->getLocation().y);  
}

void Wave::onTouchEnded(Touch* touch, Event* event) {
    //CCLOG("onTouchEnded: Location is x= %f, y=%f", touch->getLocation().x, touch->getLocation().y);

    //if (GameManager::GetInstance()->Towers.size() > 0) {
    if (chosenTower != -1 && towerMoved == false) {
        if (GameManager::GetInstance()->Towers.at(chosenTower)->GetSprite()->getBoundingBox().containsPoint(touch->getLocation())) {
            //Ulos("SAMA PISTE!!!, avaa jotain näppäimiä");

            // Selling tower is always available
            UserInterface::GetInstance()->OpenSellTowerButton(chosenTower);

            // Towers can only be upgraded once
            if (GameManager::GetInstance()->Towers.at(chosenTower)->isUpgraded() == false) {
                UserInterface::GetInstance()->OpenUpgradeTowerButton(chosenTower);
            }
            else {
                UserInterface::GetInstance()->UpgradeTowerButton->setVisible(false);
                UserInterface::GetInstance()->UpgradeTowerButton->setEnabled(false);
            }
        }
    }
    else {
        UserInterface::GetInstance()->SellTowerButton->setVisible(false);
        UserInterface::GetInstance()->SellTowerButton->setEnabled(false);
        UserInterface::GetInstance()->UpgradeTowerButton->setVisible(false);
        UserInterface::GetInstance()->UpgradeTowerButton->setEnabled(false);
    }
    towerMoved = false;
}

int Wave::GetChosenTower() {
    return chosenTower;
}

void Wave::EndGame(std::string condition) {
    unscheduleAllCallbacks();
    GameManager::GetInstance()->WaveObject->removeAllChildrenWithCleanup(true);
    Director::getInstance()->getRunningScene()->removeAllChildrenWithCleanup(true);
    GameManager::GetInstance()->Reset();
    Scene* sceneT = Scene::create();
    
    AudioEngine::stopAll();
    AudioEngine::end();
    
    Sprite* endL;
    if (condition == "win") {
        endL = Sprite::create("YouWonScreen.png");
        SoundManager::PlayWinTheme();
    }
    else {
        endL = Sprite::create("YouLostScreen.png");
        SoundManager::PlayLoseTheme();
    }
    
    endL->setPosition(Vec2(480, 320));
    sceneT->addChild(endL);
    endL->addChild(UserInterface::GetInstance()->CreateRestartButton(endL));
    Director::getInstance()->replaceScene(sceneT);
}

// Updates every frame, output commented out to reduce spam
void Wave::update(float dt) {
    if (Wave::waveN_ == Wave::nofWaves_) {
        EndGame("win");
    }
    else if (enemyN_ == waveSize_[waveN_] && GameManager::GetInstance()->Enemies.size() == 0) {
        UserInterface::GetInstance()->StartWaveButton->setEnabled(true);
        //Ulos("THE WAVE HAS ENDED. THANK YOU FOR YOUR PATIENCE");
        AudioEngine::pause(waveTheme_);
        AudioEngine::resume(menuTheme_);
        enemyN_ = -1;
        waveSection_ = 0;
        tempCount_ = -1;
        waveN_++;

        // Update wave text
        std::string number = std::to_string(waveN_ + 1);
        UserInterface::GetInstance()->RoundText->setString(number);
    }
}