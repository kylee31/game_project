#include "ItemManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

ItemManager* ItemManager::instance = 0; //const상수는 외부에서 0으로 한번 초기화해줘야함.

ItemManager::ItemManager() {
	gDis = GameDistance::GetSingleton();
	distancecount = 0;
	itemCount = 20;//아이템 처음나오는 장소
	srand((unsigned int)time(NULL));//랜덤 수

}

void ItemManager::Update() {


	if (v.size() != 0) {//벡터의 크기가 0이 아니라면
		for (int n = 0; n < v.size(); n++) {
			v.at(n).Update();//벡터 요소 하나하나를 다 위치 업뎃
			if (v.at(n).x <= 330) {//컴퓨터 화면의 끝에 도달하면
				vector<Item>::iterator it = v.begin() + n;//그 벡터 요소는 없애버림
				v.erase(it);
			}
		}
	}

	//장애물이나 아이템 만들어서 벡터에 넣기.
	if (distancecount <= gDis->distance) {//랜덤 거리 지날때마다 다시 정의
		lastBlock = gDis->distance;//장애물을 만든 위치 저장.

		int n = rand() % 4;//3~6칸마다
		distancecount = gDis->distance + n + 3;//distancecount 다시정의
		int item_n = rand() % 4;//장애물의 종류는 4개(0,1,2,3) 

		int item_y = rand() % 3;//y좌표는 0 1 2중 하나 랜덤.
		Item tempitem(item_n, item_y);//새 아이템0객체만들어서

		v.push_back(tempitem);//벡터의 맨뒤에 넣어버리기

	}
	//아이템은 랜덤으로 또 만든다. 하지만, 장애물을 이미 만든 distancecount라면 넘어간다.
	if (itemCount <= gDis->distance) {

		if (gDis->distance == lastBlock) {//장애물을 만들었던 위치와 동일하다면
			itemCount = lastBlock + 2;//지금 말고 장애물 나오고 2칸 다음에

		}
		else {
			int n = rand() % 5;//20~25칸마다 아이템 나옴.
			itemCount = gDis->distance + n + 20;//재정의
			int item_tmp_n = rand() % 10;
			int item_y = rand() % 3;//y좌표는 0 1 2중 하나 랜덤.
			int item_n;

			if (0 <= item_tmp_n&&item_tmp_n < 5) //확률로 나오게끔.
				item_n = 4;
			else if (5 <= item_tmp_n&&item_tmp_n < 9)
				item_n = 5;
			else if (item_tmp_n = 10)
				item_n = 6;
			Item tempitem(item_n, item_y);//새 아이템0객체만들어서
			v.push_back(tempitem);//벡터의 맨뒤에 넣어버리기
		}

	}
}

void ItemManager::MiniRender() {
	if (v.size() != 0) {
		for (int n = 0; n < v.size(); n++) {
			
			v.at(n).Draw();
			
		}

	}
}

void ItemManager::FullRender() {
	if (v.size() != 0) {
		for (int n = 0; n < v.size(); n++) {

			v.at(n).Draw();	
		}

	}
}

void ItemManager::Move() {
	if (v.size() != 0) {
		for (int n = 0; n < v.size(); n++) {
			v.at(n).Move();
		}

	}

}

void ItemManager::Move_c() {
	if (v.size() != 0) {
		for (int n = 0; n < v.size(); n++) {
			v.at(n).Move_c();
		}

	}

}


void ItemManager::renewal() {
	timecount = 0;
	distancecount = 0;
	lastBlock = 0;
	itemCount = 0;
	if(!v.empty())//차있다면
		v.clear();//그 벡터 비워라.
}