#pragma once

#include "CoinTower.h"
#include "GameManager.h"
#include "UserInterface.h"

USING_NS_CC;

CoinTower* CoinTower::createCoinTower(float posX, float posY) {
	auto towerOne = new CoinTower();
	if (towerOne && towerOne->init(posX, posY)) {
		towerOne->autorelease();
		return towerOne;
	}
	CC_SAFE_DELETE(towerOne);
	return nullptr;
}

bool CoinTower::init(float posX, float posY) {
	if (!Sprite::init())
	{
		return false;
	}
	name_ = "CoinTower";
	damage_ = 0;
	radius_ = 200;
	price_ = 30;
	attackSpeed_ = 1.5;
	rewardMult_ = 2;
	hitpoints_ = 2;
	image_ = Sprite::create("CoinTower.png");
	firstHit_ = false;
	upgraded_ = false;
	strongAgainst_ = None;
	weakAgainst_ = None;
	image_->setPosition(Vec2(posX, posY));
	addChild(image_);
	this->scheduleUpdate();
	return true;
}

void CoinTower::update(float dt) {
	EnemyCheck(2);
	if (firstHit_) {
		//Ulos("OSUI EKAA KERTAA");
		unscheduleUpdate();
		schedule(SEL_SCHEDULE(&BaseTower::EnemyCheck), attackSpeed_, 100, 0);
	}
}

void CoinTower::UpgradeTower() {
	if (GameManager::GetInstance()->Money >= (price_ - 10)) {
		// Only close upgrade button if tower is being upgraded
		UserInterface::GetInstance()->UpgradeTowerButton->setVisible(false);
		UserInterface::GetInstance()->UpgradeTowerButton->setEnabled(false);


		GameManager::GetInstance()->Money -= (price_ - 10);
		std::string number = std::to_string(GameManager::GetInstance()->Money);
		UserInterface::GetInstance()->MoneyText->setString(number);

		upgraded_ = true;
		rewardMult_ = 3;

	}
}

void CoinTower::EnemyCheck(float dt) {
	Vector<BaseEnemy*> enemyVector = GameManager::GetInstance()->Enemies;

	for (int i = 0; i < enemyVector.size(); i++) {
		BaseEnemy* enemy = enemyVector.at(i);
		float distance = image_->getPosition().getDistance(enemy->GetSprite()->getPosition());
		if (distance < radius_ && enemy->isWorthy() == false) {
			Attack(enemy);
			firstHit_ = true;
			break;
		}
	}
}

void CoinTower::Attack(BaseEnemy* enemyHit) {
	enemyHit->IncreaseReward(rewardMult_);
}