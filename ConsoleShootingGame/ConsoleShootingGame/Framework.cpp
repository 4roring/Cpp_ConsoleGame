#include "Framework.h"

Framework::Framework(){
	InitRank();
	Title();
}

Framework::~Framework(){
	delete player;
	delete wall;
	
	for(int i=0;i<maxEnemy;i++)
		if(enemy[i] != NULL) delete enemy[i];
}

// 초기화 후 게임으로 진입
// 업데이트 -> 렌더 -> 33/1000초 대기 -> 프레임 카운터 증가 반복
// 플레이어의 HP가 0이하가 되면 게임 오버 -> 점수 확인 후 랭랭 삽입 -> 타이틀로 이동
void Framework::Start(){
	srand(time(NULL));
	gameScreen.InitlizeScreen();

	player = new Player(20, 2);
	wall = new GameObject(0, 0, "|");
	level = 0;
	maxEnemy = 8;

	for(int i=0;i<maxEnemy;i++)
		enemy[i] = NULL;
	
	LevelManager();

	FrameCount = 0;

	while(player->Get_HP() != 0){
		Update();
		gameScreen.Render();
		Sleep(33);
		FrameCount++;
	}
	system("cls");
	GameOver();
	InsertRank(player->Get_Score());
	Title();
}

// 타이틀 화면
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
		Start();
		break;
	case 2:
		system("cls");
		ShowRank();
		system("cls");
		Title();
		break;
	default: 
		exit(1);
		break;
	}
}

// 게임 내 정보를 업데이트
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

// 플레이어의 입력을 확인하여 동작
void Framework::Input(){
	if(GetAsyncKeyState(VK_LEFT) & 0x8000){
		if(player->Get_X() > 1)
			player->Set_X(player->Get_X()-1);
	}

	if(GetAsyncKeyState(VK_UP) & 0x8000){ // 디버그용 입력
		player->Set_Score(800);
		player->Set_HP(0);
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

// 후면 버퍼에 플레이어, 벽, 적 캐릭터, 총알 등 모든 오브젝트를 그림
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

// 몬스터들과 몬스터들의 총알 상태 체크
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

// 레벨을 증가시키고 레벨 + 1만큼의 적 생성
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

// 게임 오버를 1초간 보여주는 기능
void Framework::GameOver(){
	gameScreen.Gotoxy(20, 10);
	std::cout << "Game Over";
	Sleep(1000);
	system("cls");
}

// 게임 시작시 랭킹 데이터 파일을 입력받음
// 랭킹 데이터 파일이 없으면 새로 생성 후 초기화
void Framework::InitRank(){
	std::ifstream rankInFile("Ranking.dat", std::ios::in, std::ios::binary);
	char buf[20];
	if(!rankInFile){
		//std::cout << "파일 생성" << std::endl;
		//Sleep(1000);                           // 생성 확인용 코드
		std::ofstream rankOutFile("Ranking.dat", std::ios::out, std::ios::binary);
		
		for(int i=1;i<=5;i++)
			rankOutFile << i << ' ' << 100 * (6 - i) << ' ' << "NONAME" << std::endl;

		rankOutFile.close();

		rankInFile.open("Ranking.dat", std::ios::in, std::ios::binary);
	}

	for(int i=0;i<5;i++){
		rankInFile.getline(buf,20,' ');
		//std::cout << buf << ' ';
		rankInFile.getline(buf,20,' ');
		rank[i].Score = atoi(buf); 
		//std::cout << buf << ' ';
		rankInFile.getline(buf,20);
		strcpy(rank[i].name, buf);
		//std::cout << buf << std::endl;
	}

	rankInFile.close();
}

// 랭킹을 확인하여 삽입 후 랭킹 파일 재작성
// FIXME : Input에서 발생한 입력들이 랭킹 이름 작성시 남으니 조치를 취해야함
void Framework::InsertRank(int Score){
	int nowRank = -1;
	char rankName[6];
	for(int i=0;i<5;i++){
		if(rank[i].Score < Score){
			nowRank = i;
			break;
		}
	}

	if(nowRank == -1) return;
	
	std::cout << "Score : " << player->Get_Score() << "  Rank : " << nowRank+1 << std::endl;
	std::cout << "Insert Rank Name(6 char limit) : ";
	std::cin.clear();
	std::cin >> rankName;

	if(nowRank == 4){
		rank[nowRank].Score = Score;
		strcpy(rank[nowRank].name, rankName);
	}
	else{
		for(int i=3;i>nowRank;i--){
			rank[i] = rank[i-1];
		}
		rank[nowRank].Score = Score;
		strcpy(rank[nowRank].name, rankName);
	}

	std::ofstream rankOutFile("Ranking.dat", std::ios::out, std::ios::binary);
	for(int i=1;i<=5;i++)
		rankOutFile << i << ' ' << rank[i-1].Score << ' ' << rank[i-1].name << std::endl;
	rankOutFile.close();
	system("cls");
}

// 랭킹을 2초간 보여주는 기능
void Framework::ShowRank(){
	std::cout << "========================" << std::endl << std::endl;
	std::cout << " Ranking                          " << std::endl << std::endl;
	std::cout << "========================" << std::endl;
	std::cout << " Rank    Score    Name   " << std::endl;
	
	for(int i=0;i<5;i++)
		std::cout << "   " << i+1 << "     " << rank[i].Score << "      " << rank[i].name << std::endl;
	
	std::cout << "2초 후 Title로 이동";
	Sleep(2000);
}