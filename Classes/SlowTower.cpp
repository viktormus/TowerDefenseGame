#include "SlowTower.h"
#include "GameManager.h"
#include "UserInterface.h"

USING_NS_CC;

SlowTower* SlowTower::createSlowTower(float posX, float posY) {
	auto towerOne = new SlowTower();
	if (towerOne && towerOne->init(posX, posY)) {
		towerOne->autorelease();
		return towerOne;
	}
	CC_SAFE_DELETE(towerOne);
	return nullptr;
}

bool SlowTower::init(float posX, float posY) {
	if (!Sprite::init())
	{
		return false;
	}
	name_ = "SlowTower";
	damage_ = 0;
	radius_ = 300;
	attackSpeed_ = 1.5;
	price_ = 30;
	hitpoints_ = 2;

	slow_ = 0.5;

	image_ = Sprite::create("SlowTower.png");
	firstHit_ = false;
	upgraded_ = false;
	strongAgainst_ = Fire;
	weakAgainst_ = Evolved;
	image_->setPosition(Vec2(posX, posY));
	addChild(image_);
	this->scheduleUpdate();
	return true;
}

void SlowTower::update(float dt) {
	EnemyCheck(2);
	if (firstHit_) {
		//Ulos("OSUI EKAA KERTAA");
		unscheduleUpdate();
		schedule(SEL_SCHEDULE(&BaseTower::EnemyCheck), attackSpeed_, 100, 0);
	}
}

void SlowTower::EnemyCheck(float dt) {
	//Ulos("Inside EnemyCheck");
	Vector<BaseEnemy*> enemyVector = GameManager::GetInstance()->Enemies;

	for (int i = 0; i < enemyVector.size(); i++) {
		BaseEnemy* enemy = enemyVector.at(i);
		float distance = image_->getPosition().getDistance(enemy->GetSprite()->getPosition());
		if (distance < radius_ && enemy->isSlowed() == false) {
			//Ulos("Distance towards an enemy is", distance);
			Attack(enemy);
			firstHit_ = true;
			break;
		}
	}
}

void SlowTower::Attack(BaseEnemy* enemyHit) {
	//Ulos("Inside SlowTower Attack");
	float currSlow = CompareTypes(enemyHit);
	//Ulos("currSlow:", currSlow);
	enemyHit->ReduceSpeed(currSlow);
}

float SlowTower::CompareTypes(BaseEnemy* enemy) {
	//Ulos("Inside SlowTower::CompareTypes");
	if (strongAgainst_ != None && strongAgainst_ == enemy->GetType()) {
		//Ulos("Slow increased");
		return slow_ / 1.5f;
	}
	else if (weakAgainst_ != None && weakAgainst_ == enemy->GetType()) {
		//Ulos("Slow decreased");
		return slow_ * 1.5f;
	}
	//Ulos("Slow unchanged");
	return slow_;
}

void SlowTower::UpgradeTower() {
	if (GameManager::GetInstance()->Money >= (price_ - 10)) {
		// Only close upgrade button if tower is being upgraded
		UserInterface::GetInstance()->UpgradeTowerButton->setVisible(false);
		UserInterface::GetInstance()->UpgradeTowerButton->setEnabled(false);

		//Ulos("UPGRADING TOWER :DDD");
		GameManager::GetInstance()->Money -= (price_ - 10);
		std::string number = std::to_string(GameManager::GetInstance()->Money);
		UserInterface::GetInstance()->MoneyText->setString(number);

		//Ulos("Inside SlowTowerUpgrade");
		upgraded_ = true;
		//Ulos("Slow before:", slow_);
		slow_ = 0.25;
		//Ulos("Slow after:", slow_);
	}
}