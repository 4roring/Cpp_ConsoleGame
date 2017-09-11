#include "Player.h"

Player::Player(int x, int y) : GameObject(x, y){
	image = "vAv";
	width = 3;
	height = 1;

	reload = true;
}

void Player::ShootBullet(){
	int bullet_i = -1;
	for(int i=0;i<20;i++){
		if(bullet[i] == NULL){
			bullet[i] = new GameObject(this->Get_X()+2, this->Get_Y()+1, "^");
		}
	}
}

void Player::BulletMove(GameScreen& scr){
	for(int i=0;i<20;i++){
		if(bullet[i] != NULL){
			bullet[i]->Set_Y(bullet[i]->Get_Y()+1);
		}

		scr.DrawBackBuffer(bullet[i]->Get_X(), bullet[i]->Get_Y(), bullet[i]->Get_Image());
		if(bullet[i]->Get_Y() > scr.GetScrHeight()-1){
			delete bullet[i];
		}	
	}
}



