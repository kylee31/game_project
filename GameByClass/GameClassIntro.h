#pragma once

#include "SDL.h"
#include"ItemManager.h"
#include "Teacher.h"
#include "GameDistance.h"
class Intro
{
public:
	Intro();
	~Intro();
	void HandleEvents();
	void Update();
	void Render();
	ItemManager *itemM;
	Teacher *cha;
	GameDistance *gDis;
	MyCharacter*mycha;

private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination

};


