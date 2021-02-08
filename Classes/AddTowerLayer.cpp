#include "AddTowerLayer.h"
#include "ui/CocosGUI.h"
#include "UserInterface.h"
#include <string>

USING_NS_CC;

bool AddTowerLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	mySpriteTower1_ = Sprite::create("Tower1Button.png");
	this->addChild(mySpriteTower1_);
	mySpriteTower1_->setPosition(Vec2(782, 490));
	this->addChild(tempSpriteTower1_);
	tempSpriteTower1_->setVisible(false);

	mySpriteBombTower_ = Sprite::create("BombTowerButton.png");
	this->addChild(mySpriteBombTower_);
	mySpriteBombTower_->setPosition(Vec2(888, 490));
	this->addChild(tempSpriteBombTower_);
	tempSpriteBombTower_->setVisible(false);
	
	mySpriteSlowTower_ = Sprite::create("SlowTowerButton.png");
	this->addChild(mySpriteSlowTower_);
	mySpriteSlowTower_->setPosition(Vec2(782, 365));
	this->addChild(tempSpriteSlowTower_);
	tempSpriteSlowTower_->setVisible(false);
	
	mySpriteLightningTower_ = Sprite::create("LightningTowerButton.png");
	this->addChild(mySpriteLightningTower_);
	mySpriteLightningTower_->setPosition(Vec2(888, 365));
	this->addChild(tempSpriteLightningTower_);
	tempSpriteLightningTower_->setVisible(false);

	mySpriteCoinTower_ = Sprite::create("CoinTowerButton.png");
	this->addChild(mySpriteCoinTower_);
	mySpriteCoinTower_->setPosition(Vec2(782, 240));
	this->addChild(tempSpriteCoinTower_);
	tempSpriteCoinTower_->setVisible(false);
	
	// Adding everyting to the main wave object layer
	GameManager::GetInstance()->WaveObject->addChild(this);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(AddTowerLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(AddTowerLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(AddTowerLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool AddTowerLayer::onTouchBegan(Touch* touch, Event* event) {
	// Checks whether the area being clicked is the right one I.E. is the person clicking on Tower Button
	// Must check with if/else statements, because switch requires integral or enum type
	if (mySpriteTower1_->getBoundingBox().containsPoint(touch->getLocation())) {
		if (GameManager::GetInstance()->Money >= 30) {
			//CCLOG("You are Pressing correct area");
			currClick = 0;
			currDrag = tempSpriteTower1_;
			conditionForDragging = true;
		} else {
			//CCLOG("YOU DON'T HAVE ENOUGH MONEY. YOU HAVE Money %f", GameManager::GetInstance()->Money);
			return 0;
		}
		return 1;

	} else if (mySpriteBombTower_->getBoundingBox().containsPoint(touch->getLocation())) {
		if (GameManager::GetInstance()->Money >= 50) {
			//CCLOG("You are Pressing correct area");
			currClick = 1;
			currDrag = tempSpriteBombTower_;
			conditionForDragging = true;
		}
		else {
			//CCLOG("YOU DON'T HAVE ENOUGH MONEY. YOU HAVE Money %f", GameManager::GetInstance()->Money);
			return 0;
		}
		return 1;

	} else if (mySpriteSlowTower_->getBoundingBox().containsPoint(touch->getLocation())) {
		if (GameManager::GetInstance()->Money >= 30) {
			//CCLOG("You are Pressing correct area");
			currClick = 2;
			currDrag = tempSpriteSlowTower_;
			conditionForDragging = true;
		}
		else {
			//CCLOG("YOU DON'T HAVE ENOUGH MONEY. YOU HAVE Money %f", GameManager::GetInstance()->Money);
			return 0;
		}
		return 1;

	} else if (mySpriteLightningTower_->getBoundingBox().containsPoint(touch->getLocation())) {
		if (GameManager::GetInstance()->Money >= 60) {
			//CCLOG("You are Pressing correct area");
			currClick = 3;
			currDrag = tempSpriteLightningTower_;
			conditionForDragging = true;
		}
		else {
			//CCLOG("YOU DON'T HAVE ENOUGH MONEY. YOU HAVE Money %f", GameManager::GetInstance()->Money);
			return 0;
		}
		return 1;

	} else if (mySpriteCoinTower_->getBoundingBox().containsPoint(touch->getLocation())) {
		if (GameManager::GetInstance()->Money >= 80) {
			//CCLOG("You are Pressing correct area");
			currClick = 4;
			currDrag = tempSpriteCoinTower_;
			conditionForDragging = true;
		}
		else {
			//CCLOG("YOU DON'T HAVE ENOUGH MONEY. YOU HAVE Money %f", GameManager::GetInstance()->Money);
			return 0;
		}
		return 1;
	}
return 0;
}	
	

void AddTowerLayer::onTouchMoved(Touch* touch, Event* event) {
	currDrag->setVisible(true);
	auto action = MoveTo::create(0,Vec2(touch->getLocation().x,touch->getLocation().y ));
	currDrag->runAction(action);
	//Ulos("Dragging Tower");
}

void AddTowerLayer::onTouchEnded(Touch* touch, Event* event) {
	//Ulos("onTouchEnded");
	if (conditionForDragging) {
		if (touch->getLocation().x > 700) { CCLOG("CANNOT ADD TOWER HERE"); }
		else {
			float posX = touch->getLocation().x;
			float posY = touch->getLocation().y; //pass these as parameters to function, create 
			
			if (posX > 680) {
				posX = 680;
			}
			else if (posX < 30) {
				posX = 30;
			}
			if (posY > 525) {
				posY = 525;
			}
			else if (posY < 43) {
				posY = 43;
			}
			
			BaseTower* tower;
			switch (currClick) {
			case 0:
				tower = TowerOne::createTowerOne(posX, posY);
				break;
			case 1:
				tower = BombTower::createBombTower(posX, posY);
				break;
			case 2:
				tower = SlowTower::createSlowTower(posX, posY);
				break;
			case 3:
				tower = LightningTower::createLightningTower(posX, posY);
				break;
			case 4:
				tower = CoinTower::createCoinTower(posX, posY);
				break;
			default:
				tower = TowerOne::createTowerOne(posX, posY);
			}
			
			this->addChild(tower);
			GameManager::GetInstance()->Towers.pushBack(tower);

			GameManager::GetInstance()->Money -= tower->GetPrice();
			std::string number = std::to_string(GameManager::GetInstance()->Money);
			UserInterface::GetInstance()->MoneyText->setString(number);

			//Ulos("Money:", GameManager::GetInstance()->Money);
			conditionForDragging = false;
		}
	}
	currDrag->setVisible(false);
}
