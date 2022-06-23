#pragma once

#include "SDL.h"
#include "MyCharacter.h"
#include "SDL_ttf.h"
#include "ItemManager.h"
#include "GameDistance.h"
#include "GameTime.h"
#include "Teacher.h"
#include "GameWarning.h"


class Stage2 {
public :
	Stage2();
	~Stage2();

	void HandleEvents();
	void Update();
	void Render();

	Uint32 collision_last_time;
	Uint32 shoes_last_time;
	bool collision;//이거 나중에 초기화해주기


private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination

	SDL_Texture *title_score_en;
	SDL_Rect title_score_en_rect;


	MyCharacter *my;
	ItemManager *itemM;
	GameDistance *gDis;
	GameTime *gtime;
	Teacher *cha;
	GameWarning *gWarn;


};