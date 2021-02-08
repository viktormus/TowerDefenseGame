#include "UserInterface.h"
#include "TowerOne.h"

#include <string>

USING_NS_CC;

UserInterface* UserInterface::instance;
      

UserInterface* UserInterface::GetInstance() {
    if (instance == NULL) instance = new UserInterface();
    return instance;
}

ui::Button* UserInterface::CreateRestartButton(Sprite* layer) {
    auto button = ui::Button::create("RestartNormal.png", "RestartSelected.png");
    button->setPosition(Vec2(layer->getContentSize().width / 2, 170));
    button->setVisible(true);
    button->setEnabled(true);
    button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::ENDED:
            AudioEngine::stopAll();
            Director::getInstance()->getRunningScene()->removeAllChildrenWithCleanup(true);
            Director::getInstance()->replaceScene(Wave::createScene());
            break;
        }
        });
    return button;
}

void UserInterface::CreateStartWaveButton(Layer* layer) {
    auto button = ui::Button::create("StartWaveNormal.png", "StartWaveSelected.png", "StartWaveDisabled.png");
    button->setPosition(Vec2(580, 610));
    //CCLOG( X= %f, Y= %f, X=jotakin, Y= jotakin) 
    //Ulos("CreateStartWaveButtonin sisällä!");
   
    button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            //Ulos(">>> TouchEventType BEGAN");
            break;
        case ui::Widget::TouchEventType::MOVED:
            
            //Ulos(">>> TouchEventType MOVED");
            break;
        case ui::Widget::TouchEventType::ENDED:
            //Ulos(">>> TouchEventType ENDED");
            GameManager::GetInstance()->WaveObject->WaveEvent(GameManager::GetInstance()->WaveObject->waveN_);
            AudioEngine::pause(GameManager::GetInstance()->WaveObject->menuTheme_);
            
            // First time the wave theme is started, after that it is just paused/resumed
            if (GameManager::GetInstance()->WaveObject->waveTheme_ == 1000) {
                GameManager::GetInstance()->WaveObject->waveTheme_ = SoundManager::PlayWaveTheme();
            }
            else {
                AudioEngine::resume(GameManager::GetInstance()->WaveObject->waveTheme_);
            }

            break;
        case ui::Widget::TouchEventType::CANCELED:
            //Ulos(">>> TouchEventType CANCELED");
            break;
        default:
            break;
        }
        });

    StartWaveButton = button;
    layer->addChild(button);
}


void UserInterface::CreateSellTowerButton(Layer* layer) {
    auto button = ui::Button::create("SellTowerNormal.png", "SellTowerSelected.png");
    //Ulos("SellTowerButton created!!!");

    button->setPosition(Vec2(100, 100));

    SellTowerButton = button;
    layer->addChild(button);
}

void UserInterface::OpenSellTowerButton(int tower) {
    //Ulos("Inside OpenSellTowerButton");
    //Ulos("INT TOWER:", tower);
    SellTowerButton->setEnabled(true);
    SellTowerButton->setVisible(true);

    Sprite* towerSprite = GameManager::GetInstance()->Towers.at(tower)->GetSprite();

    // Moves SellTowerButton to wherever a clicked tower is
    float posX = towerSprite->getPosition().x;
    float posY = towerSprite->getPosition().y + 25 + towerSprite->getContentSize().height / 2;
    SellTowerButton->setPosition(Vec2(posX, posY));
    
    SellTowerButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            //Ulos("Int tower inside addTouchEventListener:", tower);
            //Ulos("ChosenTower from wave object:", GameManager::GetInstance()->WaveObject->GetChosenTower());
            int chosenTower = GameManager::GetInstance()->WaveObject->GetChosenTower();
            GameManager::GetInstance()->Towers.at(chosenTower)->SellTower();
        }});
}

void UserInterface::CreateUpgradeTowerButton(Layer* layer) {
    auto button = ui::Button::create("UpgradeNormal.png", "UpgradeSelected.png");
    //Ulos("UpgradeTowerButton created!!!");

    button->setPosition(Vec2(200, 100));

    button->setEnabled(false);
    button->setVisible(false);

    UpgradeTowerButton = button;
    layer->addChild(button);
}

void UserInterface::OpenUpgradeTowerButton(int tower) {
    //Ulos("Inside OpenUpgradeTowerButton");
    //Ulos("INT TOWER:", tower);
    UpgradeTowerButton->setEnabled(true);
    UpgradeTowerButton->setVisible(true);

    Sprite* towerSprite = GameManager::GetInstance()->Towers.at(tower)->GetSprite();

    // Moves UpgradeTowerButton to wherever the clicked tower is
    float posX = towerSprite->getPosition().x;
    float posY = towerSprite->getPosition().y - 25 - towerSprite->getContentSize().height / 2;
    UpgradeTowerButton->setPosition(Vec2(posX, posY));

    UpgradeTowerButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            //Ulos("INSIDE UpgradeTowerButton");
            //Ulos("Int tower inside addTouchEventListener:", tower);
            //Ulos("ChosenTower from wave object:", GameManager::GetInstance()->WaveObject->GetChosenTower());
            int chosenTower = GameManager::GetInstance()->WaveObject->GetChosenTower();
            GameManager::GetInstance()->Towers.at(chosenTower)->UpgradeTower();
        }});
}

void UserInterface::CreateMoneyText(Layer* layer) {
    auto label = Label::createWithTTF("Money:", "fonts/Pusab.ttf", 40);
    label->setPosition(Vec2(90, 580));
    layer->addChild(label);

    std::string number = std::to_string(GameManager::GetInstance()->Money);
    label = Label::createWithTTF(number, "fonts/Pusab.ttf", 40);
    label->setPosition(Vec2(210, 580));
    MoneyText = label;
    layer->addChild(label);
}

void UserInterface::CreateRoundText(Layer* layer) {
    auto label = Label::createWithTTF("Round:", "fonts/Pusab.ttf", 40);
    label->setPosition(Vec2(90, 615));
    layer->addChild(label);

    std::string number = std::to_string(GameManager::GetInstance()->WaveObject->waveN_ + 1);
    label = Label::createWithTTF(number, "fonts/Pusab.ttf", 40);
    label->setPosition(Vec2(210, 615));
    RoundText = label;
    layer->addChild(label);
}