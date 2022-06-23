#include <iostream>
#include <vector>
#include "GameClassPhase.h"

#include "Item.h"
extern SDL_Renderer* g_renderer;



Item::Item(int a,int item_y) {

	y_num = item_y;
	x = 569;
	//장애물은 이미지만 다를뿐 그외엔 다 동일하기에 따로 클래스 구분 안했습니다!
	if (a == 0) {//0번 장애물
		SDL_Surface*temp_surface = IMG_Load("../img/0.png");
		item_source_rect.x = 0;
		item_source_rect.y = 0;
		item_source_rect.w = 80;
		item_source_rect.h = 80;
		item_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		itemType = 0;
	}
	else if (a == 1) {//1번 장애물
		SDL_Surface*temp_surface = IMG_Load("../img/1.png");
		item_source_rect.x = 0;
		item_source_rect.y = 0;
		item_source_rect.w = 80;
		item_source_rect.h = 80;
		item_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_SetTextureAlphaMod(item_texture, 20);
		SDL_FreeSurface(temp_surface);
		itemType = 1;

	}
	else if (a == 2) {//2번 장애물
		SDL_Surface*temp_surface = IMG_Load("../img/2.png");
		item_source_rect.x = 0;
		item_source_rect.y = 0;
		item_source_rect.w = 80;
		item_source_rect.h = 80;
		item_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		itemType = 2;

	}

	else if (a == 3) {//3번 장애물
		SDL_Surface*temp_surface = IMG_Load("../img/3.png");
		item_source_rect.x = 0;
		item_source_rect.y = 0;
		item_source_rect.w = 80;
		item_source_rect.h = 80;
		item_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		itemType = 3;

	}
	else if (a == 4) {//4번/ (아이템으로는 첫번째), 시계
		SDL_Surface*temp_surface = IMG_Load("../img/4.png");
		item_source_rect.x = 0;
		item_source_rect.y = 0;
		item_source_rect.w = 80;
		item_source_rect.h = 80;
		item_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		itemType = 4;

	}
	else if (a == 5) {//두번째 아이템, 신발
		SDL_Surface*temp_surface = IMG_Load("../img/5.png");
		item_source_rect.x = 0;
		item_source_rect.y = 0;
		item_source_rect.w = 80;
		item_source_rect.h = 80;
		item_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		itemType = 5;

	}
	else if (a == 6) {//세번째 아이템, 하트
		SDL_Surface*temp_surface = IMG_Load("../img/6.png");
		item_source_rect.x = 0;
		item_source_rect.y = 0;
		item_source_rect.w = 80;
		item_source_rect.h = 80;
		item_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		itemType = 6;

	}
}

Item::~Item() {
	//SDL_DestroyTexture(item_texture);
}

void Item::crush() {
	//충돌시 각자 일어나는 기능.
	// void virtual crush(); 원래 추상클래스 구현하려다가 이함수 하나만 다른거라 굳이 그래야하나?
	//하면서 itemType라는 변수를 따로 두고 그 변수에맞게 함수를 구현하는걸 생각해봤어요!

	if (0 <= itemType&&itemType < 4) {
		//장애물이랑 부딫혔을때 어쩔건지.
	}
	else if (itemType == 4) {//시계
	}
	else if (itemType == 5) {//신발
	}
	else if (itemType == 6) {//하트
	}


}
void Item::Update() {
	if (g_current_game_phase == PHASE_STAGE1) {//축소화면이라면
		item_destination_rect.h = 20;
		item_destination_rect.w = 20;
		item_destination_rect.x = x;
		item_destination_rect.y = 340 + y_num * 30;
		SDL_SetTextureAlphaMod(item_texture, 40);     //투명도 조절하기 
	}
	else {//확대화면이라면
		item_destination_rect.h = 20 * (8.0 / 2.4);
		item_destination_rect.w = 20*(8.0 / 2.4);
		item_destination_rect.x = x* (8.0 / 2.4)-348* (8.0 / 2.4);
		item_destination_rect.y = 200 + y_num * 100;
		SDL_SetTextureAlphaMod(item_texture, 250);     //투명도 조절하기
	}
}

void Item::Draw() {
	SDL_RenderCopy(g_renderer, item_texture, &item_source_rect, &item_destination_rect);//내 캐릭터 그리기

}

void Item::Move() {
	x -= 20;
}

void Item::Move_c() {
	x -= 40;
}