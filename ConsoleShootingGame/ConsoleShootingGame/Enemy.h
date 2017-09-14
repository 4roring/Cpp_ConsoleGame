#pragma once
#include "GameObject.h"
#include "GameScreen.h"

class Enemy : public GameObject{
public:
	Enemy(int x, int y);
	~Enemy(){ for(int i=0;i<5;i++) if(bullet[i]!=NULL) delete bullet[i]; }

	int Get_HP() const { return HP; }

	void Set_HP(const int value) { HP = value; }

	void CollisionEvent(GameScreen &scr);
	void ApplyDamage(const int damage);
	void EnemyMove(GameScreen& scr);
	void ShootBullet(const int FrameCount);
	void BulletMove(GameScreen& scr);
private:
	int HP;
	bool moveRight;
	int shootTimer;
	int minTime, maxTime;
	GameObject* bullet[5];
};