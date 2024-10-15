#pragma once
#include "SceneBase.h"


class Menu
{
public:
	Menu(VECTOR2 pos, std::string name, float scale);
	VECTOR2 position;//現在位置
	VECTOR2 positionB;//移動前
	VECTOR2 positionE;//移動後
	float scale;
	DWORD color;
	std::string name;
};

class MenuScene : public SceneBase
{
public:
	MenuScene();
	//~MenuScene();

	void Update()override;
	void Draw()override;

private:
	int timer;
	int changeTime;
	//メニューを並べるときの傾きの始点と終点
	VECTOR2 lineBegin;
	VECTOR2 lineEnd;
	VECTOR2 EtoB;

	VECTOR2 disPos[3];

	enum Mode//遷移先
	{
		mPlay = 0,
		mOption,
		mTitle,
	};

	CSpriteImage* back;
	CSpriteImage* image;
	CSprite* spr;

	Menu* menu[3];
	
	int select;
};
