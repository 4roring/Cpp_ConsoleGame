#pragma once
#include <fstream>
#include "GameScreen.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

typedef struct {
	int Score;
	char name[20];
}Rank;

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
	void GameOver();
	void InitRank();
	void InsertRank(int Score);
	void ShowRank();

private:
	int FrameCount;
	int maxEnemy;
	int enemyCount;
	int level;
	GameScreen gameScreen;
	Player* player;
	Enemy* enemy[8];
	GameObject* wall;
	Rank rank[5];

};