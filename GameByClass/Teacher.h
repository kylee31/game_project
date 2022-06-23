#pragma once
#include "SDL.h"
#include "GameTime.h"

class Teacher {
private:
	//double attack_power;

	Teacher();
	~Teacher();
	//내 캐릭터 객체를 한번만 생성되게끔 만들어주기위해!
	static Teacher* instance;

	SDL_Rect t_source_rect[3];
	SDL_Rect t_destination_rect[3];

	SDL_Rect t_source_rect_face[3];
	SDL_Rect t_destination_rect_face;


public:
	void Draw();
	void Update();

	//선생님 그림 배열 인덱스
	//stage에서 사용하기 위해.?
	int index;

	SDL_Texture* t_texture;
	SDL_Texture* t_texture_face;

	//void GetAttacked(double power);

	static void CreateInstance() {
		if (instance != 0) return;
		instance = new Teacher;

	}
	static Teacher* GetSingleton() {
		return instance;
	}
	int tcount;
	void renewal();
	GameTime *gtime;//시간가져다 쓰기위해

};