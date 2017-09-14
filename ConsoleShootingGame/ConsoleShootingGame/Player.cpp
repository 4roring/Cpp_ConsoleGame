#include "Player.h"

Player::Player(int x, int y) : GameObject(x, y){
	image = "vAv";
	width = 3;
	height = 1;

	reload = true;
	HP = 50;
	Score = 0;

	for(int i=0;i<20;i++)
		bullet[i] = NULL;
}

// 입력에 따른 총알 발사 이벤트
void Player::ShootBullet(){
	int bullet_i = -1;
	for(int i=0;i<20;i++){
		if(bullet[i] == NULL){
			bullet_i = i;
			bullet[i] = new GameObject(this->Get_X()+1, this->Get_Y(), "^");
			break;
		}
	}

	if(bullet_i == -1) return;
}

// 총알의 이동
void Player::BulletMove(GameScreen& scr){
	for(int i=0;i<20;i++){
		if(bullet[i] != NULL){
			bullet[i]->Set_Y(bullet[i]->Get_Y()+1);

			// 총알 충돌 체크
			if(scr.GetScrObject(bullet[i]->Get_X(), bullet[i]->Get_Y()) == 'U' ||
				scr.GetScrObject(bullet[i]->Get_X(), bullet[i]->Get_Y()) == '<' ||
				scr.GetScrObject(bullet[i]->Get_X(), bullet[i]->Get_Y()) == '>'){
				scr.DrawBackBuffer(bullet[i]->Get_X(), bullet[i]->Get_Y(), "^");
				delete bullet[i];
				bullet[i] = NULL;
				Score += 10;
				break;
			}
			
			scr.DrawBackBuffer(bullet[i]->Get_X(), bullet[i]->Get_Y(), bullet[i]->Get_Image());
			if(bullet[i]->Get_Y() > scr.GetScrHeight()-2){
				scr.DrawBackBuffer(bullet[i]->Get_X(), bullet[i]->Get_Y(), " ");
				delete bullet[i];
				bullet[i] = NULL;
				break;
			}
		}	
	}
}

// 총알과 플레이어의 충돌 체크
void Player::CollisionEvent(GameScreen& scr){
	if(scr.GetScrObject(Get_X(), Get_Y()) == 'u' ||
	scr.GetScrObject(Get_X()+1, Get_Y()) == 'u' ||
	scr.GetScrObject(Get_X()+2, Get_Y()) == 'u'){
			ApplyDamage(10);
	}
}

void Player::ApplyDamage(const int damage){
	HP -= damage;
}

