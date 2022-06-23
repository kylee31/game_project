#pragma once
#include "SDL.h"
#include "MyCharacter.h"
#include "Teacher.h"
#include"ItemManager.h"
#include "GameTime.h"
#include "GameDistance.h"
#include "GameWarning.h"

//https://blockdmask.tistory.com/308

class Stage1
{
public:
	Stage1();
	~Stage1();

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
	

	SDL_Texture *lec_texture;
	SDL_Rect lec_source;
	SDL_Rect lec_destination;

	MyCharacter *my;
	Teacher *cha;
	ItemManager *itemM;
	GameTime *gtime;
	GameDistance *gDis;
	GameWarning *gWarn;
};


