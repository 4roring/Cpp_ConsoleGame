#include "Framework.h"

Framework::Framework(){
	player = new Player(20, 2);
	wall = new GameObject(0, 0, "|");
	FrameCount = 0;
	Start();
}

Framework::~Framework(){
	delete player;
	delete wall;
}

void Framework::Start(){
	while(true){
		Update();
		gameScreen.Render();
		Sleep(33);
		FrameCount++;
	}
}

void Framework::Update(){
	Input();
	DrawObject();

	player->BulletMove(gameScreen);
}

void Framework::Input(){
	if(GetAsyncKeyState(VK_LEFT) & 0x8000){
		if(player->Get_X() > 1)
			player->Set_X(player->Get_X()-1);
	}

	if(GetAsyncKeyState(VK_RIGHT) & 0x8000){
		if(player->Get_X() < gameScreen.GetScrWidth()-player->Get_Width()-1)
			player->Set_X(player->Get_X()+1);
	}

	if(GetAsyncKeyState(VK_SPACE) & 0x8000){
		if(player->Get_Reload()){
			player->ShootBullet();
			player->Set_Reload(false);
		}
	}
	else
			player->Set_Reload(true);
}

void Framework::DrawObject(){
	char ScoreUI[50];
	sprintf(ScoreUI, "Score : %d                    HP : %d", player->Get_Score(), player->Get_HP());
	gameScreen.DrawBackBuffer(2, 0, ScoreUI); 

	for(int i=0;i<gameScreen.GetScrHeight();i++){
		gameScreen.DrawBackBuffer(0, i, wall->Get_Image());
		gameScreen.DrawBackBuffer(gameScreen.GetScrWidth()-1, i, wall->Get_Image());
	}

	gameScreen.DrawBackBuffer(player->Get_X(), player->Get_Y(), player->Get_Image());
}
