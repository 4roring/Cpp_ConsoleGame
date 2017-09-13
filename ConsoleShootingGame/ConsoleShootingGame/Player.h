#pragma once
#include "GameObject.h"
#include "GameScreen.h"

class Player : public GameObject {
public:
	Player() : GameObject(){}
	Player(int x, int y);
	~Player(){}

	int Get_HP() const { return HP; }
	int Get_Score() const { return Score; }
	bool Get_Reload() const { return reload; }

	void Set_HP(int value) { HP = value; }
	void Set_Score(int value) { Score = value; }
	void Set_Reload(bool value) { reload = value; }
	void ShootBullet();
	void BulletMove(GameScreen& scr);

private:
	int HP;
	int Score;
	bool reload;
	GameObject* bullet[20];
};

