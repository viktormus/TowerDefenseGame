#include "SoundManager.h"

USING_NS_CC;

void SoundManager::PlayEnemyDeath() {
	AudioEngine::play2d("Death.mp3");
}

void SoundManager::PlayShoot() {
	AudioEngine::play2d("Shoot1.mp3", false, 0.5F);
}

void SoundManager::PlayFreeze() {
	AudioEngine::play2d("Freeze.mp3", false, 0.5F);
}

void SoundManager::PlayCoin() {
	AudioEngine::play2d("Coin.mp3", false, 0.5F);
}

int SoundManager::PlayMenuTheme() {
	int menuTheme = AudioEngine::play2d("MenuTheme.mp3", true, 0.2F);
	return menuTheme;
}

int SoundManager::PlayWaveTheme() {
	int waveTheme = AudioEngine::play2d("WaveTheme.mp3", true, 0.2F);
	return waveTheme;
}

int SoundManager::PlayWinTheme() {
	int endTheme = AudioEngine::play2d("GameWin.mp3", false, 0.2F);
	return endTheme;
}

int SoundManager::PlayLoseTheme() {
	int endTheme = AudioEngine::play2d("GameLose.mp3", false, 0.2F);
	return endTheme;
}