#include "MyCharacter.h"
#include "GameClassPhase.h"

#include "SDL_image.h"

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool timecontrol;
extern int t;

extern int moving;

MyCharacter* MyCharacter::instance = 0;


MyCharacter::MyCharacter() {
	//내 캐릭터 이미지작업
	SDL_Surface*temp_surface = IMG_Load("../img/moving.png");
	jet_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);

	static const int left_x[5] = { 0, 75, 150 ,225 ,300};
	static const int right_x[5] = { 75, 150, 225, 300 ,375};

	for(int i=0; i<5 ; i++){
		jet_source_rect[i].x =left_x[i];
		jet_source_rect[i].y = 0;
		jet_source_rect[i].w = 75;
		jet_source_rect[i].h = 90;
	}
	
	SDL_FreeSurface(temp_surface);


	y_num = 1;//처음 내캐릭터는 중간라인에 위치시킴.
			  //폰트 load
	//game_font1 = TTF_OpenFont("../Resources/arose.ttf", 40);
	moving = 0;

	Mix_VolumeMusic(128);



}

MyCharacter::~MyCharacter() {
	SDL_DestroyTexture(jet_texture);
}


void MyCharacter::Update() {

	if (g_current_game_phase == PHASE_STAGE1)
	{
		jet_destination_rect.x = 445;
		jet_destination_rect.y = 303 + 33 * (y_num);
		jet_destination_rect.w = 50;
		jet_destination_rect.h = 60;
	}
	else if (g_current_game_phase == PHASE_STAGE2) {
		jet_destination_rect.x = 310;
		jet_destination_rect.y = 80 + 100 * (y_num);
		jet_destination_rect.w = 50 * (8.0 / 2.4);
		jet_destination_rect.h = 60 * (5.0 / 1.5);

	}
	if (moving == 0) {
		index = 0;
	}
	else if (moving == 1) {
		moveControl += 1;
		if (index == 0) {
			index = 1;
		}
		else if(index == 1 && moveControl>3) {
			index = 2;
		}
		else if (index == 2 && moveControl>6) {
			index = 3;
		}
		else if (index == 3 && moveControl>9) {
			index = 1;
			moveControl = 0;
		}
	}
	else if (moving == 2) {
		index=4;
	}

	
}

void MyCharacter::Draw() {
	SDL_RenderCopy(g_renderer, jet_texture, &jet_source_rect[index], &jet_destination_rect);//내 캐릭터 그리기

}

void MyCharacter::Renewal() {
	y_num = 1;
}

