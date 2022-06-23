#include "GameDistance.h"
#include "GameClassPhase.h"
#include <string>


extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;

GameDistance* GameDistance::instance = 0; //const상수는 외부에서 0으로 한번 초기화해줘야함.

GameDistance::GameDistance(){
	game_font1 = TTF_OpenFont("../Resources/moris.ttf", 40);

	distance = 0;

}

void GameDistance::Renewal() {
	distance = 0;
}
void GameDistance::Update() {
	int d = 100-distance/2;//목표거리 100
	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Surface *tmp_surface = TTF_RenderText_Blended(game_font1, std::to_string((long long)d).c_str(), white);

	text_time_rect_.x = 0;
	text_time_rect_.y = 0;
	text_time_rect_.w = tmp_surface->w;
	text_time_rect_.h = tmp_surface->h;

	text_time_ = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

	SDL_FreeSurface(tmp_surface);
	if (d <= 0)//게임은 10초가 지나면 자동종료후 엔딩화면으로.
	{
		g_current_game_phase = PHASE_ENDING;
	}
}

void GameDistance::Draw() {
	if (g_current_game_phase == PHASE_STAGE1)
	{ //축소화면에 맞게 거리변수 띄우고
		SDL_Rect r;
		r.x = 630;
		r.y = 40;
		r.w = text_time_rect_.w;
		r.h = text_time_rect_.h;
		SDL_RenderCopy(g_renderer, text_time_, 0, &r);
	}
	else if (g_current_game_phase == PHASE_STAGE2)
	{//확대화면에 맞게 거리변수 띄우기
		SDL_Rect r;
		r.x = 380;
		r.y = 0;
		r.w = text_time_rect_.w;
		r.h = text_time_rect_.h;
		SDL_RenderCopy(g_renderer, text_time_, 0, &r);
	}

}