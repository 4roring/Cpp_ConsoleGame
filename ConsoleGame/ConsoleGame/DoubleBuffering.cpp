#include "DoubleBuffering.h"

DoubleBuffering::DoubleBuffering(int mapX, int mapY){
	CONSOLE_CURSOR_INFO cursor;
	COORD size = {mapX, mapY};
	size_x = mapX;
	size_y = mapY+1;
	nScreenIndex = 0;

	SMALL_RECT rect;
	rect.Left = 0;
	rect.Right = mapX-1;
	rect.Top = 0;
	rect.Bottom = mapY-1;

	// 첫번째 버퍼
	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); // 버퍼 생성
	SetConsoleScreenBufferSize(hBuffer[0], size);
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);

	// 두번째 버퍼
	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); // 버퍼 생성
	SetConsoleScreenBufferSize(hBuffer[1], size);
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);

	cursor.dwSize = 1;
	cursor.bVisible = false;
	SetConsoleCursorInfo(hBuffer[0], &cursor);
	SetConsoleCursorInfo(hBuffer[1], &cursor);
}

DoubleBuffering::~DoubleBuffering(){
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}

void DoubleBuffering::BufferWrite(int x, int y, char* string){
	DWORD dw;
	COORD cursorPosition = {x, y};
	SetConsoleCursorPosition(hBuffer[nScreenIndex], cursorPosition);
	WriteFile(hBuffer[nScreenIndex], string, strlen(string), &dw, NULL);
}

void DoubleBuffering::BufferFlipping(){
	SetConsoleActiveScreenBuffer(hBuffer[nScreenIndex]);

	nScreenIndex = !nScreenIndex;
}

void DoubleBuffering::ClearBuffer(){
	COORD Coor = {0,0};
	DWORD dw;
	FillConsoleOutputCharacter(hBuffer[nScreenIndex], ' ', size_x*size_y, Coor, &dw);
}
