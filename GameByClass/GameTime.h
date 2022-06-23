#pragma once
#include "SDL_ttf.h"
#include "GameDistance.h"

class GameTime {
private:
	GameTime();
	~GameTime();
	static GameTime* instance;

	TTF_Font *game_font1;

	SDL_Texture *text_time_;
	SDL_Rect text_time_rect_;
	GameDistance *gDis;

public:
	void Draw();
	void Update();
	int bonus_time;

	static void CreateInstance() {
		if (instance != 0) return;
		instance = new GameTime;

	}
	static GameTime* GetSingleton() {
		return instance;
	}
	int time_ms;

};