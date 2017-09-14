#pragma once
#include "GameScreen.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

class Framework{
public:
	Framework();
	~Framework();
	void Start();
	void Title();
	void Update();
	void Input();
	void DrawObject();
	void EnemyStateCheck();
	void LevelManager();

private:
	int FrameCount;
	int maxEnemy;
	int enemyCount;
	int level;
	GameScreen gameScreen;
	Player* player;
	Enemy* enemy[8];
	GameObject* wall;
};