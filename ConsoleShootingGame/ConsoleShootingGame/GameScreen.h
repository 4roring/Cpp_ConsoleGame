#pragma once
#include <iostream>
#include <Windows.h>

class GameScreen{
public:
	GameScreen():SCR_HEIGHT(20), SCR_WIDTH(40){ InitlizeScreen(); }
	~GameScreen();
	void InitlizeScreen();
	void Gotoxy(const int x, const int y);
	void DrawBackBuffer(const int x, const int y, char* image);
	void Render();
	int GetScrHeight() const { return SCR_HEIGHT; }
	int GetScrWidth() const { return SCR_WIDTH; }
	char GetScrData(int x, int y) const { return backBuffer[y][x]; }

private:
	const int SCR_HEIGHT, SCR_WIDTH;
	char **frontBuffer;
	char **backBuffer;
};