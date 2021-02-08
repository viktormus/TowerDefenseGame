#pragma once
#include "cocos2d.h"
#include "GameManager.h"
#include "Ulos.h"
#include "BaseTower.h"
#include "TowerOne.h"
#include "BombTower.h"
#include "SlowTower.h"
#include "LightningTower.h"
#include "CoinTower.h"
#include "string"


USING_NS_CC;


class AddTowerLayer : public Layer{
public:
	CREATE_FUNC(AddTowerLayer);
	virtual bool init() override;

	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

private:
	Sprite* mySpriteTower1_;
	Sprite* tempSpriteTower1_ = Sprite::create("Tower1Light.png");  //INSERT TEMPORARY DRAGGING TOWER DOWN BELOW

	Sprite* mySpriteBombTower_;
	Sprite* tempSpriteBombTower_ = Sprite::create("BombTowerLight.png");
	
	Sprite* mySpriteSlowTower_;
	Sprite* tempSpriteSlowTower_ = Sprite::create("SlowTowerLight.png");

	Sprite* mySpriteLightningTower_;
	Sprite* tempSpriteLightningTower_ = Sprite::create("LightningTowerLight.png");

	Sprite* mySpriteCoinTower_;
	Sprite* tempSpriteCoinTower_ = Sprite::create("CoinTowerLight.png");

	int currClick;
	Sprite* currDrag;
	bool conditionForDragging = false;
};
