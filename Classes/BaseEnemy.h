#pragma once
#include "cocos2d.h"
#include "Ulos.h"
#include "SoundManager.h"

#include <string>

USING_NS_CC;

// Guide:
// Ligntning tower: strong against armored, weak against lightning
// Bomb tower: strong against evolved
// Freeze tower: strong against fire, weak against evolved
// Tower one: weak against armored
// Coin tower: no change


enum Attribute {
	None, // EnemyGreen
	Armored, // ArmoredEnemy
	Lightning, // EnemyYellow
	Fire, // EnemyOne
	Evolved // SplitEnemy
};

class BaseEnemy : public Sprite {
public:
	BaseEnemy();
	~BaseEnemy() {}
	virtual bool init() override;

	void NextMove();
	virtual void onDeath();
	virtual void ReduceHitpoints(float dmg);
	void ReduceSpeed(float slow);
	void IncreaseReward(int mult);

	bool isSlowed();
	bool isWorthy();
	const std::string& GetName() const;
	float GetHitpoints() const;
	Sprite* GetSprite() const;
	Attribute GetType();

protected:
	std::string name_;
	float hitpoints_;
	Sprite* baseSprite;
	float speed_;
	int reward_;
	bool slowed_ = false;
	bool worthy_ = false;
	Attribute type_;

	Point prevProperPoint;
	Point currPoint;
	Point nextPoint;
};