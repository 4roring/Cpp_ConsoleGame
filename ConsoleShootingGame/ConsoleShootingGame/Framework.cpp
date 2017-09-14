#include "Framework.h"

Framework::Framework(){
	Title();
	gameScreen.InitlizeScreen();

	srand(time(NULL));
	player = new Player(20, 2);
	wall = new GameObject(0, 0, "|");
	level = 0;
	maxEnemy = 8;

	for(int i=0;i<maxEnemy;i++)
		enemy[i] = NULL;
	
	LevelManager();

	FrameCount = 0;
	Start();
}

Framework::~Framework(){
	delete player;
	delete wall;
	
	delete[] enemy;
}

void Framework::Start(){
	while(true){
		Update();
		gameScreen.Render();
		Sleep(33);
		FrameCount++;
	}
}

void Framework::Title(){
	int num;
	std::cout << "==================================" << std::endl << std::endl;
	std::cout << " C++ Console Window Shooting Game" << std::endl << std::endl;
	std::cout << "==================================" << std::endl << std::endl;
	std::cout << "   1.Game Start  2.Rank  3.Exit" << std::endl << std::endl;
	std::cout << "Select Input Num : ";
	std::cin >> num;

	switch(num){
	case 1: 
		std::cout << "Game Start!!!" << std::endl;
		Sleep(1000);
		system("cls");
		break;
	case 2:
		std::cout << "¹Ì±¸Çö" << std::endl;
		exit(1);
		break;
	case 3: 
	exit(1);
		break;
	}
}

void Framework::Update(){
	if(enemyCount == 0)
		LevelManager();
	
	Input();
	DrawObject();
	
	player->BulletMove(gameScreen);

	if(FrameCount > 10)
		EnemyStateCheck();

	player->CollisionEvent(gameScreen);
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
	sprintf(ScoreUI, "Score:%d  HP:%d  Level:%d", player->Get_Score(), player->Get_HP(), level);
	gameScreen.DrawBackBuffer(2, 0, ScoreUI); 

	for(int i=0;i<maxEnemy;i++){
		if(enemy[i] != NULL)
			gameScreen.DrawBackBuffer(enemy[i]->Get_X(), enemy[i]->Get_Y(), enemy[i]->Get_Image());
	}

	for(int i=0;i<gameScreen.GetScrHeight();i++){
		gameScreen.DrawBackBuffer(0, i, wall->Get_Image());
		gameScreen.DrawBackBuffer(gameScreen.GetScrWidth()-1, i, wall->Get_Image());
	}

	gameScreen.DrawBackBuffer(player->Get_X(), player->Get_Y(), player->Get_Image());
}

void Framework::EnemyStateCheck(){
	for(int i=0;i<maxEnemy;i++){
		if(enemy[i] != NULL) { 
			if(FrameCount % 10-level == 0)
				enemy[i]->EnemyMove(gameScreen);
			if(FrameCount % 4 == 0)			
				enemy[i]->ShootBullet(FrameCount);

			enemy[i]->BulletMove(gameScreen);
			enemy[i]->CollisionEvent(gameScreen);
		}

		if(enemy[i] != NULL && enemy[i]->Get_HP() <= 0){
			delete enemy[i];
			enemy[i] = NULL;
			enemyCount--;
		}
	}
}

void Framework::LevelManager(){
	level++;
	enemyCount = 3 + level;
	
	if(enemyCount >= maxEnemy)
		enemyCount = maxEnemy;

	for(int i=0;i<enemyCount;i++){
		int posX = 1 + rand() % 36;
		enemy[i] = new Enemy(posX, 19-(i*2));
	}
}