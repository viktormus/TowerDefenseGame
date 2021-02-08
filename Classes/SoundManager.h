#pragma once

#include "cocos2d.h"
#include "AudioEngine.h"

class SoundManager {
public:
	static void PlayEnemyDeath();
	static void PlayShoot();
	static void PlayFreeze();
	static void PlayCoin();
	static int PlayMenuTheme();
	static int PlayWaveTheme();
	static int PlayWinTheme();
	static int PlayLoseTheme();
};

