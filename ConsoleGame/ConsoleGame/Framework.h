#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include "DoubleBuffering.h"
#include "Player.h"

class Framework{
	Player player;
	Player tail[20];
	DoubleBuffering* db_Buffering;
	clock_t curTime, oldTime;
	int frameCount;
	int mapSize;
	char **Map;
	char *gameScreen;
	int screenSize;

public:
	Framework();
	void Start();
	void Update();
	void Input();
	void Render();
	void FrameWaiting();

	void RegenItem();
	void StageSelect(const char* stageName);
}; 