#include "MenuScene.h"

MenuScene::MenuScene()
{
	lineBegin = VECTOR2(200, 50);
	lineEnd = VECTOR2(800, 550);

	EtoB = XMVector2Normalize(lineBegin - lineEnd);

	disPos[0] = lineBegin;
	disPos[1] = lineEnd + EtoB * 350;
	disPos[2] = lineEnd;
	
	menu[mPlay] = new Menu(disPos[mPlay], "Play",1.5f);
	menu[mOption] = new Menu(disPos[mOption], "Option",1.0f);
	menu[mTitle] = new Menu(disPos[mTitle], "Title",1.0f);

	select = mPlay;
	
	changeTime = 20;
	timer = changeTime;
}

void MenuScene::Update()
{
	timer++;

	CDirectInput* DI = GameDevice()->m_pDI;
	
	if (DI->CheckKey(KD_TRG, DIK_P)) {
		SceneManager::ChangeScene("PlayScene");
	}

	if (DI->CheckKey(KD_TRG, DIK_W))
	{
		select++;
		if (select > mTitle)
		{
			select = mPlay;
		}

		for (int i = 0; i < 3; i++)
		{

			menu[i]->positionB = menu[i]->positionE;
			int no = i - select;
			if (no < 0)
			{
				no = 2 + no + 1;
			}
			menu[i]->positionE = disPos[no];
		}

		timer = 0;
	}
	if (DI->CheckKey(KD_TRG, DIK_S))
	{
		select--;
		if (select < mPlay)
		{
			select = mTitle;
		}

		for (int i = 0; i < 3; i++)
		{
			menu[i]->positionB = menu[i]->positionE;
			int no = i - select;
			if (no < 0)
			{
				no = 2 + no + 1;
			}
			menu[i]->positionE = disPos[no];
		}

		timer = 0;
	}

	if (DI->CheckKey(KD_TRG, DIK_SPACE))
	{
		SceneManager::ChangeScene((menu[select]->name+"Scene"));
	}

	if (timer < changeTime)
	{
		float rate = (float)timer / (float)changeTime;
		for (int i = 0; i < 3; i++)
		{
			menu[i]->position = (menu[i]->positionE - menu[i]->positionB) * rate + menu[i]->positionB;
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			if (select == i)
			{
				menu[i]->scale = 1.5f;
				menu[i]->color = RGB(255, 255, 255);
			}
			else
			{
				menu[i]->scale = 1.0f;
				menu[i]->color = RGB(200, 170, 255);
			}
			menu[i]->position = menu[i]->positionE;
		}
	}
}

void MenuScene::Draw()
{
	for (int i = 0; i<3; i++) {
		
		GameDevice()->m_pFont->Draw(
			menu[i]->position.x, menu[i]->position.y, menu[i]->name.c_str(), 150*menu[i]->scale, menu[i]->color);
	}

	GameDevice()->m_pFont->Draw(
		100 + 10, 500 + 10, "MENU", 200, RGB(200, 170, 255));
	
	GameDevice()->m_pFont->Draw(
		100, 500, "MENU", 200, RGB(255, 255, 255));

}

Menu::Menu(VECTOR2 pos, std::string scenename, float scale)
{
	positionE = pos;
	name = scenename;
	this->scale = scale;
	color = RGB(200, 170, 255);
}
