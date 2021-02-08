#include "BombTower.h"
#include "GameManager.h"

USING_NS_CC;

BombTower* BombTower::createBombTower(float posX, float posY) {
	auto tower = new BombTower();
	if (tower && tower->init(posX, posY)) {
		tower->autorelease();
		return tower;
	}
	CC_SAFE_DELETE(tower);
	return nullptr;
}

bool BombTower::init(float posX, float posY) {
	if (!Sprite::init())
	{
		return false;
	}
	name_ = "BombTower";
	damage_ = 2;
	radius_ = 300;
	attackSpeed_ = 5.0;
	bombRadius_ = 100;
	price_ = 50;
	hitpoints_ = 2;
	image_ = Sprite::create("BombTower.png");
	firstHit_ = false;
	upgraded_ = false;
	strongAgainst_ = Evolved;
	weakAgainst_ = None;
	image_->setPosition(Vec2(posX, posY));
	addChild(image_);
	this->scheduleUpdate();
	return true;
}

void BombTower::update(float dt) {
	EnemyCheck(2);
	if (firstHit_) {
		//Ulos("OSUI EKAA KERTAA");
		unscheduleUpdate();
		schedule(SEL_SCHEDULE(&BaseTower::EnemyCheck), attackSpeed_, 100, 0);
	}
}

void BombTower::Attack(BaseEnemy* enemyHit) {
	//Ulos("Inside BombTower Attack");
	Vector<BaseEnemy*> enemyVector = GameManager::GetInstance()->Enemies;
	for (int i = 0; i < enemyVector.size(); i++) {
		BaseEnemy* enemy = enemyVector.at(i);
		if (enemyHit != enemy) {
			float distance = enemyHit->GetSprite()->getPosition().getDistance(enemy->GetSprite()->getPosition());
			if (distance < bombRadius_) {
				float currDamage = CompareTypes(enemy);
				enemy->ReduceHitpoints(currDamage);
			}
		}
	}
	float currDamage = CompareTypes(enemyHit);
	enemyHit->ReduceHitpoints(currDamage);
}