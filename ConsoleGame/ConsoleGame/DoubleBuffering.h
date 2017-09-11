#pragma once
#include <Windows.h>
#include <iostream>

class DoubleBuffering{
	HANDLE hBuffer[2];
	int nScreenIndex;
	int size_x, size_y;
public:
	DoubleBuffering(int mapX, int mapY);
	~DoubleBuffering();
	void gotoxy(int x, int y, HANDLE g_hBuffer);
	void BufferWrite(int x, int y, char *string);
	void BufferFlipping();
	void ClearBuffer();
};