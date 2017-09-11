#pragma once
#include <iostream>
#include <Windows.h>

class GameScreen{
public:
	GameScreen():SCR_HEIGHT(20), SCR_WIDTH(40){ InitlizeScreen();};
	~GameScreen();
	void InitlizeScreen();
	void Gotoxy(const int x, const int y);
	void DrawBackBuffer(const int x, const int y, char* image);
	void Render();
	const int GetScrHeight() { return SCR_HEIGHT; }
	const int GetScrWidth() { return SCR_WIDTH; }

private:
	const int SCR_HEIGHT, SCR_WIDTH;
	char **frontBuffer;
	char **backBuffer;
};