#include "SDL.h"
#include <iostream>
#include "SDL_mixer.h"

#include "GameClassPhase.h"

#include "GameClassIntro.h"
#include "GameClassRule.h"
#include "GameClassRule2.h"
#include "GameClassStage1.h"
#include "GameClassStage2.h"
#include "GameClassEnding.h"
#include "GameClassEnding2.h"
#include "GameClassEnding3.h"
#include "GameClassHidden.h"

/////////////////////////////////////////////////
// Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;

bool g_flag_running;//전체 게임프로젝트 진행
Uint32 g_last_time_ms;
int g_frame_time_ms = 30;

bool InitializeWindow(const char* title, int xpos, int ypos, int width, int height, int fullscreen);
void CleanWindow();


// Game Phases
int g_current_game_phase;

int t;
int lec;//강의화면 제어변수
int warn;//경고누적
int moving;
bool shoes;

int a;

int main(int argc, char* argv[])
{
	InitializeWindow("Game By Class", 10, 50, 800, 500, false);

	TTF_Init();

	// Open the audio device 
	int audio_rate = 44100;//MIX_DEFAULT_FREQUENCY;
	Uint16 audio_format = MIX_DEFAULT_FORMAT;
	int audio_channels = 2;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, 4096) < 0)
	{
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		Mix_CloseAudio();
	}
	else
	{
		// For debug
		Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
		printf("Opened audio at %d Hz %d bit %s\n", audio_rate,
			(audio_format & 0xFF),
			(audio_channels > 2) ? "surround" :
			(audio_channels > 1) ? "stereo" : "mono");

	}

	Rule rule;
	Rule2 rule2;
	Stage1 stage1;
	Stage2 stage2;
	Ending ending;
	Ending2 ending2;
	Ending3 ending3;
	Intro intro;
	Hidden hidden;

	g_current_game_phase = PHASE_INTRO;

	while ( g_flag_running )
	{
		Uint32 cur_time_ms = SDL_GetTicks();
		if ( cur_time_ms-g_last_time_ms < g_frame_time_ms )
			continue;

		if ( g_current_game_phase ==  PHASE_INTRO )
		{
			intro.HandleEvents();
			intro.Update();
			intro.Render();
		}
		
		else if (g_current_game_phase == PHASE_RULE) {
			rule.HandleEvents();
			rule.Update();
			rule.Render();
		}
		else if (g_current_game_phase == PHASE_RULE2) {
			rule2.HandleEvents();
			rule2.Update();
			rule2.Render();
		}
		else if ( g_current_game_phase == PHASE_STAGE1 )
		{
			stage1.HandleEvents();
			stage1.Update();
			stage1.Render();
		}
		else if (g_current_game_phase == PHASE_STAGE2)
		{
			stage2.HandleEvents();
			stage2.Update();
			stage2.Render();
		}
		else if ( g_current_game_phase == PHASE_ENDING )
		{
			ending.HandleEvents();
			ending.Update();
			ending.Render();
		}
		else if (g_current_game_phase == PHASE_ENDING2)
		{
			ending2.HandleEvents();
			ending2.Update();
			ending2.Render();
		}
		else if (g_current_game_phase == PHASE_ENDING3)
		{
			ending3.HandleEvents();
			ending3.Update();
			ending3.Render();
		}
		else if (g_current_game_phase == PHASE_HIDDEN)
		{
			hidden.HandleEvents();
			hidden.Update();
			hidden.Render();
		}

		g_last_time_ms = cur_time_ms;
	}

	CleanWindow();

	TTF_Quit();
	Mix_CloseAudio();

	return 0;
}


////////////////////////////////////
// Functions for the Window
bool InitializeWindow(const char* title, int xpos, int ypos, int width, int height, int fullscreen)
{
	int flags = 0;
	if(fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// attempt to initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		// init the window
		g_window = SDL_CreateWindow(title, xpos, ypos, 
			width, height, flags);

		if(g_window != 0) // window init success
		{
			std::cout << "window creation success\n";
			g_renderer = SDL_CreateRenderer(g_window, -1, 0);
			if(g_renderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(g_renderer, 
					255,255,255,255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}
	std::cout << "init success\n";
	g_flag_running = true; // everything inited successfully, start the main loop

	return true;
}



void CleanWindow()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(g_window);
	SDL_DestroyRenderer(g_renderer);
	SDL_Quit();
}