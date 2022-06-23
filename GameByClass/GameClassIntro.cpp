#include "GameClassIntro.h"
#include "GameClassPhase.h"
#include "SDL_image.h"
#include <iostream>


extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
bool timecontrol;//타이머 제어해주는 변수
extern bool shoes;
extern int moving;
extern int lec;

extern int a;


Intro::Intro()
{
	// 게임인트로(gamestart)화면 이미지 작업

	SDL_Surface* temp_surface = IMG_Load("../img/start.jpg");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);

	destination_rectangle_.x = source_rectangle_.x = 0;
	destination_rectangle_.y = source_rectangle_.y = 0;
	destination_rectangle_.w = source_rectangle_.w = 800;
	destination_rectangle_.h = source_rectangle_.h = 500;

	timecontrol = false;

	cha = Teacher::GetSingleton();//선생님 초기화 위해서
	itemM = ItemManager::GetSingleton();//아이템 초기화 위해서
	gDis = GameDistance::GetSingleton();
	mycha = MyCharacter::GetSingleton();
	moving = 0;
}

Intro::~Intro()
{
	SDL_DestroyTexture(texture_);
}

void Intro::Update()
{
}


void Intro::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // 렌더정리

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Intro::HandleEvents()
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
				g_current_game_phase = PHASE_RULE;
				timecontrol = true; //시간제어변수를 true로 바꿔줌.
				itemM->renewal(); //아이템 초기화
				cha->renewal(); //선생님 초기화
				gDis->Renewal(); //거리 초기화
				moving = 0; //애니메이션 초기화
				shoes = false;
				lec = 0; //강의화면 상태 초기화
				mycha->Renewal(); //캐릭터 위치 초기화
				a = 0;
			}
			break;

		default:
			break;
		}
	}
}
