#include "Player.h"

Player::Player(int x, int y) : GameObject(x, y){
	image = "vAv";
	width = 3;
	height = 1;

	reload = true;

	for(int i=0;i<20;i++)
		bullet[i] = NULL;
}

void Player::ShootBullet(){
	int bullet_i = -1;
	for(int i=0;i<20;i++){
		if(bullet[i] == NULL){
			bullet[i] = new GameObject(this->Get_X()+1, this->Get_Y(), "^");
			break;
		}
	}
}

void Player::BulletMove(GameScreen& scr){
	for(int i=0;i<20;i++){
		if(bullet[i] != NULL){
			bullet[i]->Set_Y(bullet[i]->Get_Y()+1);
			scr.DrawBackBuffer(bullet[i]->Get_X(), bullet[i]->Get_Y(), bullet[i]->Get_Image());
			if(bullet[i]->Get_Y() > scr.GetScrHeight()-2){
				scr.DrawBackBuffer(bullet[i]->Get_X(), bullet[i]->Get_Y(), " ");
				delete bullet[i];
				bullet[i] = NULL;
			}
		}	
	}
}



