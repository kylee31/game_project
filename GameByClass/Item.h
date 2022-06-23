#pragma once

#include "MyCharacter.h"
#include "SDL_image.h"
#include "SDL.h"
//장애물끼리는 이미지 다르기때문에 클래스동일하게 두었습니다! 
//나중에 아이템은 이미지와, 충돌시 작동하는 함수정도만 다를것같아 가상함수로 구현하는것이 좋을것같아요!

class Item {
public:
	int itemType;
	int x;
	int y_num;
	~Item();
	Item();
	bool block;

	Item(int a,int item_y);//아이템 사진 업로드하게끔+y위치 랜덤( 장애물은 사진만 다르게 )
	void Draw();
	void Move();//앞으로 한칸씩옴.
	void Update();
	void crush();//충돌시 각자 일어나는 기능.
	// void virtual crush(); 원래 추상클래스 구현하려다가 이함수 하나만 다른거라 굳이 그래야하나?
	//하면서 itemType라는 변수를 따로 두고 그 변수에맞게 함수를 구현하는걸 생각해봤어요!
	void Move_c();

	SDL_Rect item_source_rect;
	SDL_Rect item_destination_rect;
	SDL_Texture* item_texture;

private:

};
