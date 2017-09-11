#include "GameScreen.h"

GameScreen::~GameScreen(){
	for(int i=0;i<SCR_WIDTH;i++){
		delete[] *(frontBuffer+i);
		delete[] *(backBuffer+i);
	}
	delete[] *frontBuffer;
	delete[] *backBuffer;
}

void GameScreen::InitlizeScreen(){
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);


	frontBuffer = new char*[SCR_HEIGHT];
	backBuffer = new char*[SCR_HEIGHT];

	for(int i=0;i<SCR_HEIGHT;i++){
		*(frontBuffer+i) = new char[SCR_WIDTH];
		*(backBuffer+i) = new char[SCR_WIDTH];
	}

	for(int y=0;y<SCR_HEIGHT;y++)
		for(int x=0;x<SCR_WIDTH;x++){
			frontBuffer[y][x] = '\0';
			backBuffer[y][x] = '\0';
		}
}

void GameScreen::Gotoxy(const int x, const int y){
	const COORD cursorPos = {x, SCR_HEIGHT - y - 1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cursorPos); 
}

void GameScreen::DrawBackBuffer(const int x, const int y, char* image){
	int tmp_x = 0;
	while(true){
		if(image[tmp_x] == '\0') break;

		if(image[tmp_x] != '\0'){
			backBuffer[y][x+tmp_x] = image[tmp_x];
			tmp_x++;
		}
	}
}

void GameScreen::Render(){
	for(int y=0;y<SCR_HEIGHT;y++)
		for(int x=0;x<SCR_WIDTH;x++){
			if(backBuffer[y][x] != frontBuffer[y][x]){
				Gotoxy(x, y);
				if(backBuffer[y][x] == '\0')
					std::cout << ' ';
				else
					std::cout << backBuffer[y][x];
			}
		}

	for(int y=0;y<SCR_HEIGHT;y++)
		for(int x=0;x<SCR_WIDTH;x++){
			frontBuffer[y][x] = backBuffer[y][x];
			backBuffer[y][x] = '\0';
		}
}
