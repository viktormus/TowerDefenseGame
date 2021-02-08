#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Ulos.h"
#include "GameManager.h"
#include "AudioEngine.h"

USING_NS_CC;

class UserInterface {
public:
	static UserInterface* GetInstance();
	void CreateStartWaveButton(Layer* layer);
	void CreateSellTowerButton(Layer* layer);
	void OpenSellTowerButton(int tower);
	void CreateUpgradeTowerButton(Layer* layer);
	void OpenUpgradeTowerButton(int tower);
	void CreateMoneyText(Layer* layer);
	void CreateRoundText(Layer* layer);
	ui::Button* CreateRestartButton(Sprite* layer);

	ui::Button* StartWaveButton;
	ui::Button* SellTowerButton;
	ui::Button* UpgradeTowerButton;
	Label* MoneyText;
	Label* RoundText;
private:
	static UserInterface* instance;
};