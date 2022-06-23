#pragma once


#include<vector>
#include"Item.h"
#include "GameTime.h"
#include "GameDistance.h"

using namespace std;

class ItemManager {
private:
	ItemManager();
	static ItemManager* instance;

public:

	vector <Item> v;

	double timecount = 0;
	int distancecount = 0;

	int lastBlock = 0;
	int itemCount = 0;

	GameDistance *gDis;

	void MiniRender();
	void FullRender();//나중에 투명도 조절할거라 나눠놈!

	void Update();
	void Move();
	void Move_c();
	void renewal();

	static void CreateInstance() {
		if (instance != 0) return;
		instance = new ItemManager;

	}
	static ItemManager* GetSingleton() {
		return instance;
	}



};