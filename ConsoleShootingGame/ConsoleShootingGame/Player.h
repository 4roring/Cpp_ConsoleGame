#pragma once
#include "GameObject.h"
#include "GameScreen.h"

class Player : public GameObject {
public:
	Player() : GameObject(){}
	Player(int x, int y);
	~Player(){ for(int i=0;i<5;i++) if(bullet[i]!=NULL) delete bullet[i];}

	int Get_HP() const { return HP; }
	int Get_Score() const { return Score; }
	bool Get_Reload() const { return reload; }

	void Set_HP(const int value) { HP = value; }
	void Set_Score(const int value) { Score = value; }
	void Set_Reload(const bool value) { reload = value; }

	void ShootBullet();
	void BulletMove(GameScreen& scr);
	void CollisionEvent(GameScreen& scr);
	void ApplyDamage(const int damage);

private:
	int HP;
	int Score;
	bool reload;
	GameObject* bullet[20];
};

