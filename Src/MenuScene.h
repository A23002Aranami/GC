#pragma once
#include "SceneBase.h"


class Menu
{
public:
	Menu(VECTOR2 pos, std::string name, float scale);
	VECTOR2 position;//���݈ʒu
	VECTOR2 positionB;//�ړ��O
	VECTOR2 positionE;//�ړ���
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
	//���j���[����ׂ�Ƃ��̌X���̎n�_�ƏI�_
	VECTOR2 lineBegin;
	VECTOR2 lineEnd;
	VECTOR2 EtoB;

	VECTOR2 disPos[3];

	enum Mode//�J�ڐ�
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
