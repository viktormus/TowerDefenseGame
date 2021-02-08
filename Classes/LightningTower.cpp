#pragma once

#include "LightningTower.h"
#include "GameManager.h"

USING_NS_CC;

LightningTower* LightningTower::createLightningTower(float posX, float posY) {
	auto towerOne = new LightningTower();
	if (towerOne && towerOne->init(posX, posY)) {
		towerOne->autorelease();
		return towerOne;
	}
	CC_SAFE_DELETE(towerOne);
	return nullptr;
}

bool LightningTower::init(float posX, float posY) {
	if (!Sprite::init())
	{
		return false;
	}
	name_ = "LightningTower";
	damage_ = 2;
	radius_ = 200;
	price_ = 60;
	attackSpeed_ = 1.5;
	hitpoints_ = 2;
	image_ = Sprite::create("LightningTower.png");
	firstHit_ = false;
	upgraded_ = false;
	strongAgainst_ = Armored;
	weakAgainst_ = Lightning;
	image_->setPosition(Vec2(posX, posY));
	addChild(image_);
	this->scheduleUpdate();
	return true;
}

void LightningTower::update(float dt) {
	EnemyCheck(2);
	if (firstHit_) {
		//Ulos("OSUI EKAA KERTAA");
		unscheduleUpdate();
		schedule(SEL_SCHEDULE(&BaseTower::EnemyCheck), attackSpeed_, 100, 0);
	}
}
void LightningTower::Attack(BaseEnemy* enemyHit) {
	//Ulos("The tower attacks", enemyHit->GetName());
	//Ulos("In vector, this enemy is #", GameManager::GetInstance()->Enemies.getIndex(enemyHit));
	float currDamage = CompareTypes(enemyHit);
	//Ulos("currDamage:", currDamage);
	enemyHit->ReduceHitpoints(currDamage);
}