#include"GameClassStage2.h"
#include "GameClassPhase.h"
#include <iostream>
#include "SDL_image.h"
#include "SDL_mixer.h"

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;

extern bool g_flag_running;
extern int moving;
extern int warn;

extern bool shoes;

Mix_Chunk *wave;
Mix_Chunk *wave_2;

Stage2::Stage2() {
	//stage2의 배경이미지 작업
	SDL_Surface* temp_surface = IMG_Load("../img/space.jpg");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	destination_rectangle_.x = source_rectangle_.x = 0;
	destination_rectangle_.y = source_rectangle_.y = 0;
	destination_rectangle_.w = 800;
	destination_rectangle_.h = 500;

	gtime = GameTime::GetSingleton();
	my = MyCharacter::GetSingleton();
	itemM = ItemManager::GetSingleton();
	gDis = GameDistance::GetSingleton();
	cha = Teacher::GetSingleton();
	gWarn = GameWarning::GetSingleton();

	moving = 0;

	shoes = false;
	collision = false;

	wave = Mix_LoadWAV("../Resources/shout.wav");
	if (wave == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	wave_2 = Mix_LoadWAV("../Resources/eating.wav");
	if (wave_2 == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}

}

Stage2::~Stage2() {
	SDL_DestroyTexture(texture_);
	SDL_DestroyTexture(title_score_en);
	if (wave) Mix_FreeChunk(wave);
	if (wave_2) Mix_FreeChunk(wave_2);
}



void Stage2::Render() {

	SDL_SetRenderDrawColor(g_renderer, 0, 255, 255, 0);
	SDL_RenderClear(g_renderer); // 렌더정리

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_); //배경화면 그림.

	itemM->FullRender();//아이템벡터
	my->Draw();//내 캐릭터 그림
	gtime->Draw();
	cha->Draw();//선생님
	gDis->Draw();
	gWarn->Draw();
	
	SDL_RenderPresent(g_renderer); // draw to the screen



}

void Stage2::Update() {
	my->Update();//내캐릭터 변동사항 업뎃
	itemM->Update();
	gtime->Update();
	cha->Update();
	gDis->Update();
	gWarn->Update();

	if (itemM->v.size() != 0) {//벡터의 크기가 0이 아니라면
		for (int n = 0; n < itemM->v.size(); n++) {
			if (itemM->v.at(n).y_num == my->y_num && (-25<445 - (itemM->v.at(n).x) && 445 - (itemM->v.at(n).x)<15)) {


				if (0 <= itemM->v.at(n).itemType && itemM->v.at(n).itemType < 4) {
					//장애물이랑 부딫혔을때 어쩔건지.
					collision_last_time = SDL_GetTicks();
					collision = true;
					Mix_PlayChannel(-1, wave, 0);
				}

				if (itemM->v.at(n).itemType == 4) {//시계
					gtime->bonus_time += 10;
					Mix_PlayChannel(-1, wave_2, 0);
				}
				if (itemM->v.at(n).itemType == 5) {//신발
					shoes = true;
					shoes_last_time = SDL_GetTicks();
					Mix_PlayChannel(-1, wave_2, 0);
				}
				if (itemM->v.at(n).itemType == 6) {//하트
					warn -= 1;
					if (warn < 1) {
						warn = 0;
						Mix_PlayChannel(-1, wave_2, 0);
					}
				}

				vector<Item>::iterator it = itemM->v.begin() + n;//그 벡터 요소는 없애버림
				itemM->v.erase(it);
			}
		}
	}

	if (collision) {//충돌되어있는 상태라면, 2초동안은 아무것도 받지 말아야한다.
		Uint32 collision_cur_time = SDL_GetTicks();
		int col_time = collision_cur_time - collision_last_time;
		moving = 2;
		if (col_time > 3000) {//3초이후에는 충돌상태를 풀어준다.
			collision = false;
			moving = 0;

		}
	}
	if (shoes) {
		Uint32 shoes_cur_time = SDL_GetTicks();
		int col_time = shoes_cur_time - shoes_last_time;
		if (col_time > 10000) {//10초이후에는 신발 부스터 상태를 풀어준다.
			shoes = false;
		}
	}
	if (PHASE_ENDING <= g_current_game_phase&&g_current_game_phase <= PHASE_HIDDEN)
		Mix_FadeOutMusic(200);
}

void Stage2::HandleEvents() {

	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;


		case SDL_KEYDOWN:
			// If the left arrow key is pressed. 
			if (event.key.keysym.sym == SDLK_UP)
			{

				if (!collision) {
					if (my->y_num != 0)//가장위쪽 라인에 있는 것이아니라면
						my->y_num--; //위쪽 한칸이동.
				}
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				if (!collision) {
					if (my->y_num != 2)//가장 아래쪽 라인이 있는 것이 아니면
						my->y_num++; // 아래로 한칸이동.
				}
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)//오른쪽버튼을 누르면
			{
				if (!collision) {
					itemM->Move();//아이템벡터들 한칸씩 이동하여 다가옴
					gDis->distance += 1;
					moving = 1;

					if (shoes) {
						itemM->Move_c();
					}
				}
			}
			if (event.key.keysym.sym == SDLK_RETURN) {//엔터누르면
				g_current_game_phase = PHASE_STAGE1;//축소화면(stage1)으로 이동
			}
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_RIGHT) {
				moving = 0;
			}

		default:
			break;
		}
	}
}