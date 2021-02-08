#include "BaseTower.h"
#include "GameManager.h"
#include "UserInterface.h"

USING_NS_CC;

BaseTower::BaseTower() {
	name_ = "BaseTower";
	hitpoints_ = 0;
	damage_ = 0;
	radius_ = 0;
	attackSpeed_ = 0;
	price_ = 0;
	image_ = nullptr;
	firstHit_ = false;
	upgraded_ = false;
	strongAgainst_ = None;
	weakAgainst_ = None;
}

bool BaseTower::init() {
	if (!Sprite::init()) {
		return false;
	}
	return true;
}

void BaseTower::EnemyCheck(float dt) {
	//Ulos("Inside EnemyCheck");
	Vector<BaseEnemy*> enemyVector = GameManager::GetInstance()->Enemies;

	// Calculating distance towards enemies and attacking if within range
	for (int i = 0; i < enemyVector.size(); i++) {
		BaseEnemy* enemy = enemyVector.at(i);
		float distance = image_->getPosition().getDistance(enemy->GetSprite()->getPosition());
		if (distance < radius_) {
			//Ulos("Distance towards an enemy is", distance);
			Attack(enemy);
			firstHit_ = true;
			break;
		}
	}
}



float BaseTower::CompareTypes(BaseEnemy* enemy) {
	//Ulos("Inside CompareTypes");
	if (strongAgainst_ != None && strongAgainst_ == enemy->GetType()) {
		//Ulos("Damage increased");
		return damage_ * 2;
	}
	else if (weakAgainst_ != None && weakAgainst_ == enemy->GetType()) {
		//Ulos("Damage decreased");
		return damage_ / 2;
	}
	//Ulos("Damage unchanged");
	return damage_;
}

void BaseTower::SellTower() {
	//Ulos("Inside SellTower");
	UserInterface::GetInstance()->SellTowerButton->setVisible(false);
	UserInterface::GetInstance()->SellTowerButton->setEnabled(false);
	UserInterface::GetInstance()->UpgradeTowerButton->setVisible(false);
	UserInterface::GetInstance()->UpgradeTowerButton->setEnabled(false);

	GameManager::GetInstance()->Money += price_ / 2;
	//Ulos("Money:", GameManager::GetInstance()->Money);

	std::string number = std::to_string(GameManager::GetInstance()->Money);
	UserInterface::GetInstance()->MoneyText->setString(number);

	this->unscheduleAllCallbacks();
	GameManager::GetInstance()->Towers.eraseObject(this);
	removeFromParent();
	//Ulos("Towers vector size:", GameManager::GetInstance()->Towers.size());
}

void BaseTower::UpgradeTower() {
	if (GameManager::GetInstance()->Money >= (price_ - 10)) {
		// Only close upgrade button if tower is being upgraded
		UserInterface::GetInstance()->UpgradeTowerButton->setVisible(false);
		UserInterface::GetInstance()->UpgradeTowerButton->setEnabled(false);

		//Ulos("UPGRADING TOWER :DDD");
		GameManager::GetInstance()->Money -= (price_ - 10);
		std::string number = std::to_string(GameManager::GetInstance()->Money);
		UserInterface::GetInstance()->MoneyText->setString(number);

		upgraded_ = true;
		//Ulos("Current damage:", damage_);
		damage_ += damage_;
		//Ulos("New damage:", damage_);
	}
}


// Getter functions

const std::string& BaseTower::GetName() const {
	return name_;
}

float BaseTower::GetDamage() {
	return damage_;
}
float BaseTower::GetRadius() {
	return radius_;
}
float BaseTower::GetAS() {
	return attackSpeed_;
}

Sprite* BaseTower::GetSprite() const {
	return image_;
}

int BaseTower::GetPrice() {
	return price_;
}

bool BaseTower::isUpgraded() {
	return upgraded_;
}