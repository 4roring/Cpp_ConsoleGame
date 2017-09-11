#include "SnakeGame.h"

SnakeGame::SnakeGame(){
	cout << "Overriding 1 " << endl;
	Start();
}

void SnakeGame::Start(){
	cout << "Overriding 2 " << endl;
	Update();
}

void SnakeGame::Update(){
	cout << "Update È£Ãâ" << endl;
}

void SnakeGame::Render(){
	cout << "Overriding 3 " << endl;
}

