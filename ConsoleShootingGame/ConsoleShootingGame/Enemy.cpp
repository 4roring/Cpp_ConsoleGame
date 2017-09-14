#include "Enemy.h"

Enemy::Enemy(int x, int y) : GameObject(x, y){
	image = "<U>";
	width = 3;
	height = 1;

	HP = 30;
	moveRight = true;
	minTime = 40;
	maxTime = 50;
	shootTimer = minTime + rand()% maxTime;

	for(int i=0;i<5;i++)
		bullet[i] = NULL;
}

// 스크린 좌표 이미지를 확인하여 총알과 충돌 이벤트
void Enemy::CollisionEvent(GameScreen &scr){
	if(scr.GetScrObject(Get_X(), Get_Y()) == '^' ||
		scr.GetScrObject(Get_X()+1, Get_Y()) == '^' ||
		scr.GetScrObject(Get_X()+2, Get_Y()) == '^'){
			ApplyDamage(10);
	}
}

// 데미지 이벤트
void Enemy::ApplyDamage(const int damage){
	HP-=damage;
}

// 일정한 속도의 좌, 우 이동
void Enemy::EnemyMove(GameScreen &scr){
	if(moveRight){
		Set_X(Get_X()+1);
		if(scr.GetScrObject(Get_X()+Get_Width()-1, Get_Y()) == '|'){
			Set_X(Get_X()-1);
			moveRight = false;
		}
	}
	else{
		Set_X(Get_X()-1);
		if(scr.GetScrObject(Get_X(), Get_Y()) == '|'){
			Set_X(Get_X()+1);
			moveRight = true;
		}
	}
}

// 프레임 카운트에 따른 총알 발사
void Enemy::ShootBullet(const int FrameCount){
	if(FrameCount % 300 == 0){
		if(minTime > 10){
			minTime--;
			maxTime--;
		}
	}
	if(FrameCount % shootTimer == 0){
		int bullet_i = -1;
		for(int i=0;i<5;i++){
			if(bullet[i] == NULL){
				bullet_i = i;
				bullet[i] = new GameObject(Get_X()+1, Get_Y(), "u");
				break;
			}
		}
		if(bullet_i == -1) return;
	}
}

// 총알의 이동 & 스크린 좌표를 확인한 충돌
void Enemy::BulletMove(GameScreen& scr){
	for(int i=0;i<5;i++){
		if(bullet[i] != NULL){
			bullet[i]->Set_Y(bullet[i]->Get_Y()-1);
			scr.DrawBackBuffer(bullet[i]->Get_X(), bullet[i]->Get_Y(), bullet[i]->Get_Image());

			if(scr.GetScrObject(bullet[i]->Get_X(), bullet[i]->Get_Y()) == 'A' ||
				scr.GetScrObject(bullet[i]->Get_X(), bullet[i]->Get_Y()) == 'v'){
				scr.DrawBackBuffer(bullet[i]->Get_X(), bullet[i]->Get_Y(), "^");
				delete bullet[i];
				bullet[i] = NULL;
				break;
			}

			if(bullet[i]->Get_Y() <= 1){
				scr.DrawBackBuffer(bullet[i]->Get_X(), bullet[i]->Get_Y(), " ");
				delete bullet[i];
				bullet[i] = NULL;
				break;
			}
		}
	}
}