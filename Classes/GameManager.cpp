#pragma once
#include "GameManager.h"

USING_NS_CC;
GameManager* GameManager::instance;

void GameManager::Reset() {
	instance = NULL;
	Money = 30;
}

GameManager* GameManager::GetInstance() {
	if (instance == NULL) instance = new GameManager();
	return instance;
}

// Automated setup of path textures throughout the path
void GameManager::CreatePathTexture(Layer* layer) {
	Layer* pathLayer = Layer::create();

	for (unsigned int i = 0; i < Path.size() - 1; i++) {
		Sprite* pathTile = Sprite::create("PathTile.png");
		pathTile->setPosition(Path.at(i));
		pathLayer->addChild(pathTile);

		if (Path.at(i + 1).x > Path.at(i).x) {
			for (float j = Path.at(i).x + 50.0f; j < Path.at(i + 1).x; j += 50.0f) {
				pathTile = Sprite::create("PathTile.png");
				pathTile->setPosition(j, Path.at(i).y);
				pathLayer->addChild(pathTile);
			}
		}
		else if (Path.at(i + 1).x < Path.at(i).x) {
			for (float j = Path.at(i).x - 50.0f; j > Path.at(i + 1).x; j -= 50.f) {
				pathTile = Sprite::create("PathTile.png");
				pathTile->setPosition(j, Path.at(i).y);
				pathLayer->addChild(pathTile);
			}
		}
		else if (Path.at(i + 1).y > Path.at(i).y) {
			for (float j = Path.at(i).y + 50.0f; j < Path.at(i + 1).y; j += 50.0f) {
				pathTile = Sprite::create("PathTile.png");
				pathTile->setPosition(Path.at(i).x, j);
				pathLayer->addChild(pathTile);
			}
		}
		else {
			for (float j = Path.at(i).y - 50.0f; j > Path.at(i + 1).y; j -= 50.0f) {
				pathTile = Sprite::create("PathTile.png");
				pathTile->setPosition(Path.at(i).x, j);
				pathLayer->addChild(pathTile);
			}
		}
	}
	Sprite* lastTile = Sprite::create("PathTile.png");
	lastTile->setPosition(Path.at(Path.size() - 1));
	pathLayer->addChild(lastTile);

	layer->addChild(pathLayer);
}