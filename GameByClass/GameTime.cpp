#include "GameTime.h"
#include "GameClassPhase.h"
#include <string>

extern int ending_page;
extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool timecontrol;
extern int t;

GameTime* GameTime::instance = 0; //const상수는 외부에서 0으로 한번 초기화해줘야함.

GameTime::GameTime() {
	//폰트 load
	game_font1 = TTF_OpenFont("../Resources/moris.ttf", 40);
	time_ms = 0;
	bonus_time = 0;
	gDis= GameDistance::GetSingleton();
}

GameTime::~GameTime() {
}

void GameTime::Draw() {
	if (g_current_game_phase == PHASE_STAGE1)
	{ //축소화면에 맞게 time변수 띄우고
		SDL_Rect r;
		r.x = 330;
		r.y = 40;
		r.w = text_time_rect_.w;
		r.h = text_time_rect_.h;
		SDL_RenderCopy(g_renderer, text_time_, 0, &r);
	}
	else if (g_current_game_phase == PHASE_STAGE2)
	{//확대화면에 맞게 time변수 띄우기
		SDL_Rect r;
		r.x = 140;
		r.y = 0;
		r.w = text_time_rect_.w;
		r.h = text_time_rect_.h;
		SDL_RenderCopy(g_renderer, text_time_, 0, &r);
	}
}



void GameTime::Update() {

	Uint32 cur_time = SDL_GetTicks();
	static Uint32 last_time = SDL_GetTicks();

	if (timecontrol == true) {//intro에서 클릭했을때 타이머 제어변수가 true가 한번되는데
		last_time = cur_time;//이때 last_time을 조정해줌.
		timecontrol = false;
		bonus_time = 0;

		//MiniResize();
	}
	time_ms = cur_time - last_time;
	//int time_ms = cur_time - last_time;
	t = 60-(time_ms / 1000) + bonus_time; //지금은 60초짜리 게임.


	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Surface *tmp_surface = TTF_RenderText_Blended(game_font1, std::to_string((long long)t).c_str(), white);

	text_time_rect_.x = 0;
	text_time_rect_.y = 0;
	text_time_rect_.w = tmp_surface->w;
	text_time_rect_.h = tmp_surface->h;

	text_time_ = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

	SDL_FreeSurface(tmp_surface);

	if (t <= 0)//게임은 10초가 지나면 자동종료후 엔딩화면으로.
	{
		last_time = cur_time;
		g_current_game_phase = PHASE_ENDING2;

		if (gDis->distance == 0) {
			g_current_game_phase = PHASE_HIDDEN;
		}
	}

}