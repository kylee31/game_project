#include "GameClassRule2.h"
#include "GameClassPhase.h"
#include "SDL_image.h"
#include <iostream>
#include "SDL_mixer.h"


extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
Mix_Music *music1;


Rule2::Rule2()
{
	// 게임인트로(gamestart)화면 이미지 작업

	SDL_Surface* temp_surface = IMG_Load("../img/rule2.jpg");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);

	destination_rectangle_.x = source_rectangle_.x = 0;
	destination_rectangle_.y = source_rectangle_.y = 0;
	destination_rectangle_.w = source_rectangle_.w = 800;
	destination_rectangle_.h = source_rectangle_.h = 500;

	Mix_VolumeMusic(128);

	music1 = Mix_LoadMUS("../Resources/lovely.mp3");
	if (!music1)
	{
		printf(" %s\n", Mix_GetError());
	}


}

Rule2::~Rule2()
{
	SDL_DestroyTexture(texture_);
	if (music1) Mix_FreeMusic(music1);

}

void Rule2::Update()
{
}


void Rule2::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // 렌더정리

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Rule2::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT) //마우스 왼쪽클릭하면 게임시작화면으로
			{
				Mix_FadeInMusic(music1, -1, 2000);
				g_current_game_phase = PHASE_STAGE1;
			}
			break;

		default:
			break;
		}
	}
}
