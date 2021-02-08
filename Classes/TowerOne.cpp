#include "TowerOne.h"
#include "GameManager.h"

USING_NS_CC;

TowerOne* TowerOne::createTowerOne(float posX, float posY) {
	auto towerOne = new TowerOne();
	if (towerOne && towerOne->init(posX, posY)) {
		towerOne->autorelease();
		return towerOne;
	}
	CC_SAFE_DELETE(towerOne);
	return nullptr;
}

bool TowerOne::init(float posX, float posY) {
	if (!Sprite::init())
	{
		return false;
	}
	name_ = "TowerOne";
	damage_ = 2;
	radius_ = 200;
	price_ = 30;
	attackSpeed_ = 1.5;
	hitpoints_ = 2;
	image_ = Sprite::create("Tower1.png");
	firstHit_ = false;
	upgraded_ = false;
	strongAgainst_ = None;
	weakAgainst_ = Armored;
	image_->setPosition(Vec2(posX, posY));
	addChild(image_);
	this->scheduleUpdate();
	return true;
}


void TowerOne::update(float dt) {
	EnemyCheck(2);
	if (firstHit_) {
		unscheduleUpdate();
		schedule(SEL_SCHEDULE(&BaseTower::EnemyCheck), attackSpeed_, 100, 0);
	}
}

void TowerOne::Attack(BaseEnemy* enemyHit) {
	//Ulos("The tower attacks", enemyHit->GetName());
	//Ulos("In vector, this enemy is #", GameManager::GetInstance()->Enemies.getIndex(enemyHit));
	float currDamage = CompareTypes(enemyHit);
	//Ulos("currDamage:", currDamage);
	enemyHit->ReduceHitpoints(currDamage);
}