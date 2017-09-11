#include <iostream>
#include <Windows.h>
#include <conio.h>

const int SCR_WIDTH = 40, SCR_HEIGHT = 20, MAX_BULLETS = 20;

typedef struct object{
	int state;
	int width;
	int height;

	int pos_x;
	int pos_y;

	char *image;
}Object;

Object player;
Object enemy;
Object *pBullet_array[MAX_BULLETS];

int score = 0;

char front_buffer[SCR_HEIGHT][SCR_WIDTH];
char back_buffer[SCR_HEIGHT][SCR_WIDTH];

void GotoXY(const int x, const int y){
	const COORD pos = {x, SCR_HEIGHT - y -1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void DrawToBackBuffer(const int x, const int y, char* image){
	int xx = 0;
	while(true){
		if(image[xx] == '\0') break;

		if(image[xx] != '\0'){
			back_buffer[y][x+xx] = image[xx];
			xx++;
		}
	}
}

void Render(){
	// re-draw changed part
	for(int i=0;i<SCR_HEIGHT;i++){
		for(int j=0;j<SCR_WIDTH;j++){
			if(back_buffer[i][j] != front_buffer[i][j]){
				GotoXY(j,i);
				if(back_buffer[i][j] == '\0')
					std::cout << ' ';
				else
					std::cout << back_buffer[i][j];
			}
		}
	}

	for(int i=0;i<SCR_HEIGHT;i++){
		for(int j=0;j<SCR_WIDTH;j++){
			front_buffer[i][j] = back_buffer[i][j];
			back_buffer[i][j] = '\0';
		}
	}
}

void shootBullet(){
	int b_ix = -1;
	for(int i=0;i<MAX_BULLETS;i++){
		if(pBullet_array[i] == NULL)
		{
			b_ix = i;
			break;
		}
	}

	if(b_ix == -1) return;


	pBullet_array[b_ix] = new Object;
		
	pBullet_array[b_ix] ->pos_x = player.pos_x + 2;
	pBullet_array[b_ix] ->pos_y = player.pos_y;
	pBullet_array[b_ix] ->image = "n";
}



void darwBoundary(){
	int i = 0;
	for (int j=0;j<SCR_HEIGHT;j++){
		DrawToBackBuffer(i,j,"l");
	}

	i = SCR_WIDTH -1;
	for (int j=0;j<SCR_HEIGHT;j++){
		DrawToBackBuffer(i,j,"l");
	}
}

void DrawObject(){
	// draw player
	DrawToBackBuffer(player.pos_x, player.pos_y, player.image);

	// draw enemy
	char *current_state_image = enemy.image + (enemy.width+1) * enemy.state;

	DrawToBackBuffer(enemy.pos_x, enemy.pos_y, current_state_image);

	

	if(enemy.state > 0)
		enemy.state--;

	// darw a bullet
	for(int i = 0;i<MAX_BULLETS;i++){
		if(pBullet_array[i] != NULL){
			if(pBullet_array[i]->pos_y >= SCR_HEIGHT - 1){
				delete pBullet_array[i];
				pBullet_array[i] = NULL;
			}
			else{
				DrawToBackBuffer(pBullet_array[i]->pos_x, pBullet_array[i]->pos_y, pBullet_array[i]->image);
				pBullet_array[i]->pos_y++;


				// check collision between enemy and bullet
				if(pBullet_array[i]->pos_y == enemy.pos_y && 
					pBullet_array[i]->pos_x >= enemy.pos_x && pBullet_array[i]->pos_x < enemy.pos_x + enemy.width){
						score++;
						enemy.state = 5;
				}
			}
		}
	}
}

int main(){
	CONSOLE_CURSOR_INFO curinfo;
	curinfo.dwSize = 1;
	curinfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);

	// initialize bullet array
	for(int i=0;i<MAX_BULLETS;i++){
		pBullet_array[i] = NULL;
	}

	// initialize buffers
	for(int i=0;i<SCR_HEIGHT;i++)
		for(int j=0;j<SCR_WIDTH;j++){
			front_buffer[i][j] = '\0';
			back_buffer[i][j] = '\0';
		}

	player.image = ">-0-<";
	player.width = 5;
	player.height = 1;
	player.pos_x = 10;
	player.pos_y = 5;

	enemy.state = 0;
	enemy.image = "[^O^]\0[xOx]\0[xOx]\0[xOx]\0[xOx]\0[xOx]";
	enemy.width = 5;
	enemy.height = 1;
	enemy.pos_x = 10;
	enemy.pos_y = SCR_HEIGHT - 4;

	while(true){
		if(GetAsyncKeyState(VK_LEFT) & 0x8000){
			if(player.pos_x > 1)
				player.pos_x--;
		}

		if(GetAsyncKeyState(VK_RIGHT) & 0x8000){
			if(player.pos_x < SCR_WIDTH - player.width - 1)
			player.pos_x++;
		}

		if(GetAsyncKeyState(VK_UP) & 0x8000){
			player.pos_y++;
		}

		if(GetAsyncKeyState(VK_DOWN) & 0x8000){
			player.pos_y--;
		}

		static bool reloaded = true;  

		if(GetAsyncKeyState(VK_SPACE) & 0x8000){
			if(reloaded == true){
				shootBullet();
				reloaded = false;
			}
		}
		else{
			reloaded = true;
		}

		darwBoundary();

		const int dice = rand() % 3; // 0:stay, 1:left, 2:right

		switch(dice){
		case 0:
			break;
		case 1:
			if(enemy.pos_x > 0)
				enemy.pos_x--;
			break;
		case 2:
			if(enemy.pos_x < SCR_WIDTH - enemy.width - 1)
				enemy.pos_x++;
			break;
		}

		GotoXY(15, SCR_HEIGHT -1);
		char scoreText[15];
		sprintf(scoreText, "Score : %d", score);
		DrawToBackBuffer(15,SCR_HEIGHT - 1,scoreText);


		DrawObject();

		Render();
		
		Sleep(30);
	}

	for(int i=0;i<MAX_BULLETS;i++){
		if(pBullet_array[i] != NULL){
			delete pBullet_array[i];
		}
	}

	return 0;
}