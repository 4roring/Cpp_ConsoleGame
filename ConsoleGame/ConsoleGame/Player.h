#pragma once
enum MoveDir { Up, Down, Right, Left };
             // 0    1     2      3
class Player{
	int x, y;
	int tail;
	int moveSpeed; // m/s
	MoveDir moveDir;
	bool GameOver;
public:
	Player();

	//Get 함수
	const int GetX(){ return x; }
	const int GetY(){ return y; }
	const int GetMoveSpeed(){ return moveSpeed; }
	const int GetTail(){ return tail; }
	const MoveDir GetMoveDir(){ return moveDir; }
	const bool GetGameOver(){ return GameOver; }
	
	//Set 함수
	void SetX(const int x){ this->x = x; }
	void SetY(const int y){ this->y = y; }
	void SetMoveSpeed(const float speed){ moveSpeed = speed; }
	void SetTail(const int tail){ this->tail = tail; }
	void SetMoveDir(const MoveDir dir){ moveDir = dir; }
	void SetGameOver(const bool gameover){ GameOver = gameover; }
};