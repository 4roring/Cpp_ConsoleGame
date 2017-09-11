#pragma once
#include "GameScreen.h"
#include "GameObject.h"
#include "Player.h"

class Framework{
public:
	Framework();
	~Framework();
	void Start();
	void Update();
	void Input();
	void DrawObject();
private:
	int FrameCount;
	GameScreen gameScreen;
	Player* player;
	GameObject* wall;
};