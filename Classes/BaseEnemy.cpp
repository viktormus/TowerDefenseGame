#pragma once

#include "BaseEnemy.h"
#include "GameManager.h"
#include "UserInterface.h"
#include <vector>

USING_NS_CC;

BaseEnemy::BaseEnemy() {
	name_ = "BaseEnemy";
	hitpoints_ = 0;
	baseSprite = nullptr;
	speed_ = 0;
	reward_ = 0;
	type_ = None;
	prevProperPoint = Point(0, 0);
	currPoint = Point(0, 0);
	nextPoint = Point(0, 0);
}

void BaseEnemy::NextMove() {
	std::vector<Point> points = GameManager::GetInstance()->Path;
	//Ulos("inside NextMove");

	if (baseSprite->getPosition() == points.at(points.size() - 1)) {
		//Ulos("Enemy #", GameManager::GetInstance()->Enemies.getIndex(this), "has reached the end of path and is being deleted now.");
		onDeath();
		GameManager::GetInstance()->WaveObject->EndGame("lose");
		return;
	}

	bool isAtPoint = false;

	// Checking whether the enemy is exactly at some Path point
	for (unsigned int i = 0; i < points.size(); i++) {
		if (baseSprite->getPosition() == points.at(i)) {
			isAtPoint = true;
			currPoint = points.at(i);
			nextPoint = points.at(i + 1);
			prevProperPoint = points.at(i);
		}
	}

	// Finding between which points the current sprite position is, and determining the nextPoint from that
	// Tää on eka kohta koko projektissa johon mun pitää käyttää kynää ja paperia jotta voin hahmottaa sen :DD
	if (!isAtPoint) {
		currPoint = baseSprite->getPosition();
		for (unsigned int i = 0; i < points.size() - 1; i++) {
			if (points.at(i).y == currPoint.y && points.at(i + 1).y == currPoint.y) {
				if ((points.at(i).x <= currPoint.x && points.at(i + 1).x >= currPoint.x) || (points.at(i).x >= currPoint.x && points.at(i + 1).x <= currPoint.x)) {
					nextPoint = points.at(i + 1);
					prevProperPoint = points.at(i);
					break;
				}
			}
			else if (points.at(i).x == currPoint.x && points.at(i + 1).x == currPoint.x) {
				if ((points.at(i).y <= currPoint.y && points.at(i + 1).y >= currPoint.y) || (points.at(i).y >= currPoint.y && points.at(i + 1).y <= currPoint.y)) {
					nextPoint = points.at(i + 1);
					prevProperPoint = points.at(i);
					break;
				}
			}
		}	
	}

	//Ulos("Previous proper point coordinates:", prevProperPoint.x, prevProperPoint.y);
	//Ulos("Current point coordinates:", currPoint.x, currPoint.y);
	//Ulos("Next point coordinates:", nextPoint.x, nextPoint.y);

	float duration = currPoint.getDistance(nextPoint) / speed_;

	baseSprite->runAction(Sequence::create(MoveTo::create(duration, nextPoint), CallFuncN::create(CC_CALLBACK_0(BaseEnemy::NextMove, this)), NULL));
}


bool BaseEnemy::init() {
	if (!Sprite::init()) {
		return false;
	}
	return true;
}

void BaseEnemy::onDeath() {
	//Ulos("Inside onDeath - the enemy has died.");
	SoundManager::PlayEnemyDeath();
	this->unscheduleAllCallbacks();
	GameManager::GetInstance()->Enemies.eraseObject(this);
	removeFromParent();
}

void BaseEnemy::ReduceHitpoints(float dmg) {
	SoundManager::PlayShoot();
	hitpoints_ -= dmg;
	if (hitpoints_ <= 0) {
		//Ulos("The enemy has been killed.");
		GameManager::GetInstance()->Money += reward_;

		// Updating money text
		std::string number = std::to_string(GameManager::GetInstance()->Money);
		UserInterface::GetInstance()->MoneyText->setString(number);

		//Ulos("BANK ACCOUNT:", GameManager::GetInstance()->Money);
		onDeath();
	}
}

void BaseEnemy::ReduceSpeed(float slow) {
	SoundManager::PlayFreeze();
	//Ulos("Inside ReduceSpeed");
	speed_ = speed_ * slow;
	slowed_ = true;
	//Ulos("New speed:", speed_);

	// Interrupting current NextMove and starting it again with updated speed
	this->unscheduleAllCallbacks();
	// Comment out the next line if you want to see some cool action :DD
	baseSprite->stopAllActions();
	NextMove();
}

void BaseEnemy::IncreaseReward(int mult) {
	SoundManager::PlayCoin();
	worthy_ = true;
	reward_ = reward_ * mult;
}


// Getter functions

bool BaseEnemy::isSlowed() {
	return slowed_;
}

bool BaseEnemy::isWorthy() {
	return worthy_;
}

float BaseEnemy::GetHitpoints() const {
	return hitpoints_;
}

Sprite* BaseEnemy::GetSprite() const {
	return baseSprite;
}

Attribute BaseEnemy::GetType() {
	return type_;
}

const std::string& BaseEnemy::GetName() const {
	return name_;
}