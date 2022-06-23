#include "GameClassStage1.h"
#include "GameClassPhase.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include<vector>

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int lec;

extern int moving;
extern bool shoes;
extern int warn;

Mix_Chunk *wave1;
Mix_Chunk *wave2;

Stage1::Stage1()
{
		// 축소화면(stage1)의 배경이미지 작업
		SDL_Surface* temp_surface = IMG_Load("../img/main.jpg");
		texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);

		SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
		destination_rectangle_.x = source_rectangle_.x = 0;
		destination_rectangle_.y = source_rectangle_.y = 0;
		destination_rectangle_.w = source_rectangle_.w;
		destination_rectangle_.h = source_rectangle_.h;

		GameDistance::CreateInstance();//itemmanager(아이템벡터)클래스역시 한번만 만들어줌.
		gDis = GameDistance::GetSingleton();

		GameTime::CreateInstance(); //MyCharacter의 클래스는 객체를 한번만 만들 예정.
		gtime = GameTime::GetSingleton();

		MyCharacter::CreateInstance(); //MyCharacter의 클래스는 객체를 한번만 만들 예정.
		my = MyCharacter::GetSingleton();
		//my->MiniResize();//내캐릭터 사이즈 조정
		
		Teacher::CreateInstance();//teacher클래스역시 한번만 만들어줌.
		cha = Teacher::GetSingleton();

		ItemManager::CreateInstance();//itemmanager(아이템벡터)클래스역시 한번만 만들어줌.
		itemM = ItemManager::GetSingleton();

		GameWarning::CreateInstance();//itemmanager(아이템벡터)클래스역시 한번만 만들어줌.
		gWarn = GameWarning::GetSingleton();


		//수업화면
		SDL_Surface* lec_surface = IMG_Load("../img/lecture.jpg");
		lec_texture = SDL_CreateTextureFromSurface(g_renderer, lec_surface);
		SDL_FreeSurface(lec_surface);

		SDL_QueryTexture(lec_texture, NULL, NULL, &lec_source.w, &lec_source.h);
		lec_source.x = 0;
		lec_source.y = 0;

		lec_destination.x = 349;
		lec_destination.y = 281;
		lec_destination.w = 240;
		lec_destination.h = 150;
		
		moving = 0;
		shoes = false;
		collision = false;

		Mix_VolumeMusic(128);

		wave1 = Mix_LoadWAV("../Resources/shout.wav");
		if (wave1 == NULL)
		{
			printf("Couldn't load the wav: %s\n", Mix_GetError());
		}
		wave2 = Mix_LoadWAV("../Resources/eating.wav");
		if (wave2 == NULL)
		{
			printf("Couldn't load the wav: %s\n", Mix_GetError());
		}
}

Stage1::~Stage1()
{
	SDL_DestroyTexture(texture_);
	SDL_DestroyTexture(lec_texture);
	SDL_DestroyTexture(title_score_en);
	if (wave1) Mix_FreeChunk(wave1);
	if (wave2) Mix_FreeChunk(wave2);
}


void Stage1::Update() {
	gtime->Update();

	my->Update();//내 캐릭터 변동사항 업뎃
	itemM->Update();
	cha->Update();
	gDis->Update();
	gWarn->Update();

	//아이템&장애물의 벡터와 캐릭터가 충돌 했는지 안했는지 검사
	//캐릭터의 x좌표는 정해져있다.
	//미니에서는 캐릭터 x 중간 위치
	//미니 = > 445
	if (itemM->v.size() != 0) {//벡터의 크기가 0이 아니라면
		for (int n = 0; n < itemM->v.size(); n++) {
			if (itemM->v.at(n).y_num == my->y_num&&(-25<445-(itemM->v.at(n).x)&&445 - (itemM->v.at(n).x)<15)) {

				if (0 <= itemM->v.at(n).itemType && itemM->v.at(n).itemType < 4) {
					//장애물이랑 부딫혔을때 어쩔건지.
					collision_last_time = SDL_GetTicks();
					collision = true;
					Mix_PlayChannel(-1, wave1, 0);
				}

				if (itemM->v.at(n).itemType == 4) {//시계
					gtime->bonus_time += 10;
					Mix_PlayChannel(-1, wave2, 0);
				}
				if (itemM->v.at(n).itemType == 5) {//신발
					shoes = true;
					shoes_last_time= SDL_GetTicks();
					Mix_PlayChannel(-1, wave2, 0);
				}
				if (itemM->v.at(n).itemType == 6) {//하트
					warn -= 1;
					if (warn < 1) {
						warn = 0;
						Mix_PlayChannel(-1, wave2, 0);
					}
				}
				vector<Item>::iterator it = itemM->v.begin() + n;//그 벡터 요소는 없애버림
				itemM->v.erase(it);
			}
			
		}
	}
	if (collision) {//충돌되어있는 상태라면, 2초동안은 아무것도 받지 말아야한다.
		Uint32 collision_cur_time = SDL_GetTicks();
		int col_time = collision_cur_time -collision_last_time;
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

void Stage1::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 0,255,255,0);
	SDL_RenderClear(g_renderer); //렌더 정리

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_); //stage1배경

	itemM->MiniRender();//아이템벡터


	my->Draw();//내캐릭터
	cha->Draw();//선생님
	gtime->Draw();
	gDis->Draw();
	gWarn->Draw();


	if (lec == 1)//tab을 눌러진 상태라면 강의화면을 마지막에 덮어버린다.
	{
		SDL_RenderCopy(g_renderer, lec_texture, &lec_source, &lec_destination);

	}

	SDL_RenderPresent(g_renderer); // draw to the screen
}

void Stage1::HandleEvents()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_UP)
			{
				if(lec==0){
					if(!collision){
						if (my->y_num != 0)//가장위쪽 라인에 있는 것이아니라면
						my->y_num--; //내 캐릭터 위쪽 한칸이동.
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				if(lec==0){
					if(!collision){
						if (my->y_num != 2)//가장 아래쪽 라인이 있는 것이 아니면
						my->y_num++; // 내 캐릭터아래로 한칸이동.
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)//오른쪽버튼을 누르면
			{
				if (lec == 0) {
					if (!collision) {
						itemM->Move();//아이템벡터들 한칸씩 이동하여 다가옴
						gDis->distance += 1;
						moving = 1;
						
						if (shoes)
						{
							itemM->Move_c();
						}
					}
				}

			}
			if (event.key.keysym.sym == SDLK_SPACE) // tab키를 누르면, lec상태바꿔줌.
			{
				if (lec == 0)
				{
					lec = 1;
				}
				else if (lec == 1)
				{
					lec = 0;
				}

			}
			if (event.key.keysym.sym == SDLK_RETURN) { //엔터를 누르면
				if(lec==0)
					g_current_game_phase = PHASE_STAGE2; // 확대화면(stage2)로 이동
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
