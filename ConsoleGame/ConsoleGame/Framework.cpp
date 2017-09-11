#include "Framework.h"

Framework::Framework(){
	srand(time(NULL));

	// 콘솔창 커서 제거
	//CONSOLE_CURSOR_INFO curInfo;
	//GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	//curInfo.bVisible = false;
	//SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

	char* stage = new char[10];
	std::cout << "스테이지 입력" << std::endl;
	std::cout << "1. stage1,txt" << std::endl; 
	std::cout << "2. stage2.txt" << std::endl; 
	std::cout << "3. stage3.txt" << std::endl; 
	std::cin >> stage;

	switch(*stage){
	case '1' : stage = "stage1.txt";
		break;
	case '2' : stage = "stage2.txt";
		break;
	case '3' : stage = "stage3.txt";
		break;
	default :
		break;
	}

	StageSelect(stage);
	RegenItem();
	Start();
}

void Framework::Start(){
	frameCount = 0;
	oldTime = clock();
	while(!player.GetGameOver()){
		Update();
		Render();
		FrameWaiting();
	}
	std::cout << "Game Over" << std::endl;
}

// 게임내 데이터를 업데이트
void Framework::Update(){
	if(kbhit()) // 입력 확인
		Input();

	if(frameCount % player.GetMoveSpeed() == 0){ // 프레임에 따라 플레이어 이동
		int tmpX;
		int tmpY;

		if(player.GetTail() == 0){
			Map[player.GetY()][player.GetX()] = '0';
			tmpX = player.GetX();
			tmpY = player.GetY();
		}
		else{
			tmpX = tail[player.GetTail()-1].GetX();
			tmpY = tail[player.GetTail()-1].GetY();
			Map[tmpY][tmpX] = '0';

			for(int i=player.GetTail()-1;i!=0;--i){
				tail[i].SetX(tail[i-1].GetX()); 
				tail[i].SetY(tail[i-1].GetY()); 
			}

			tail[0].SetX(player.GetX());
			tail[0].SetY(player.GetY());
		}

		// 플레이어의 이동 상태에 따라 그 방향으로 계속 이동
		switch(player.GetMoveDir()){
		case Up :
			player.SetY(player.GetY()-1);
			break;
		case Down :
			player.SetY(player.GetY()+1);
			break;
		case Left :
			player.SetX(player.GetX()-1);
			break;
		case Right :
			player.SetX(player.GetX()+1);
			break;
		}

		// 2(아이템)을 먹으면 새로운 위치에 아이템 생성
		if(Map[player.GetY()][player.GetX()] == '2'){
			RegenItem();
			tail[player.GetTail()].SetX(tmpX);
			tail[player.GetTail()].SetY(tmpY);
			player.SetTail(player.GetTail() + 1);
			player.SetMoveSpeed(player.GetMoveSpeed() - 1);
		}

		// 플레이어의 위치가 1(벽) 또는 3(플레이어 자신)일 경우 게임오버
		if(Map[player.GetY()][player.GetX()] == '1' ||
			Map[player.GetY()][player.GetX()] == '3')
			player.SetGameOver(true);
	}

	// 플레이어의 위치는 3을 넣어준다
	Map[player.GetY()][player.GetX()] = '3';

	// 꼬리의 개수에 따라 그 위치에 3을 넣어준다
	if(player.GetTail() > 0){
		for(int i=0;i<player.GetTail();i++)
			Map[tail[i].GetY()][tail[i].GetX()] = '3';
	}
}

// 입력을 확인
void Framework::Input(){
	char hitKey = getch();
	switch(hitKey){
	case 'w':
		player.SetMoveDir(Up);
		break;
	case 's':
		player.SetMoveDir(Down);
		break;
	case 'a':
		player.SetMoveDir(Left);
		break;
	case 'd':
		player.SetMoveDir(Right);
		break;
	}
}

// Update 된 데이터를 그린다.
void Framework::Render(){
	//std::cout << "FrameCount : " << frameCount << std::endl;
	char TailSize[50];
	sprintf(TailSize, "꼬리의 개수 : %d\n", player.GetTail());
	strcat(gameScreen, TailSize);
	//std::cout << "꼬리의 개수 : " << player.GetTail() << std::endl;
	for(int i=0;i<mapSize;i++){
		for(int j=0;j<mapSize;j++){
			if(Map[i][j] == '0'){
				//std::cout << "  ";
				std::strcat(gameScreen, "  ");
			}
			else if(Map[i][j] == '1'){
				//std::cout << "■";
				std::strcat(gameScreen, "■");
			}
			else if(Map[i][j] == '2'){
				//std::cout << "●";
				std::strcat(gameScreen, "●");
			}
			else if(Map[i][j] == '3'){
				//std::cout << "○";
				std::strcat(gameScreen, "○");
			}
		}
		//std::cout << std::endl;
		strcat(gameScreen, "\n");
	}

	db_Buffering->BufferWrite(0, 0, gameScreen);
	//system("cls");
}

// 1프레임 대기
void Framework::FrameWaiting(){
	while(1){
		curTime = clock();
		if(curTime - oldTime > 33){
			oldTime = curTime;
			break;
		}
	}
	frameCount++;
	db_Buffering->BufferFlipping();
	db_Buffering->ClearBuffer();
	for(int i=0;i<screenSize;i++)
		gameScreen[i] = NULL;
}

// 아이템을 리젠
void Framework::RegenItem(){
	while(1){
		int regenX = rand()%mapSize;
		int regenY = rand()%mapSize;

		if(Map[regenY][regenX] == '0'){
			Map[regenY][regenX] = '2';
			break;
		}
	}
}

void Framework::StageSelect(const char* stageName){
	std::ifstream stageFile(stageName, std::ios::in);
	char* inputString = new char[100];

	if(!stageFile){
		std::cout << "파일이 없습니다" << std::endl;
		exit(0);
	}

	stageFile.getline(inputString, 100);
	mapSize = std::atoi(inputString);

	Map = new char*[mapSize];
	for(int i=0;i<mapSize;i++)
		*(Map+i) = new char[mapSize+1];


	screenSize = mapSize*(mapSize*2)+mapSize;
	gameScreen = new char[screenSize];

	for(int i=0;i<screenSize;i++)
		gameScreen[i] = NULL;
	

	db_Buffering = new DoubleBuffering(mapSize*2, mapSize*2);

	int i=0;
	while(!stageFile.eof()){
		stageFile.getline(inputString, 100);
		strcpy(Map[i], inputString);
		i++;
	}
}