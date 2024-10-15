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

	back = new CSpriteImage( GameDevice()->m_pShader,"Data/Image/MenuBack.png");
	image = new CSpriteImage( GameDevice()->m_pShader,"Data/Image/Menu.png");

	spr = new CSprite();
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
			
			if (select == i)
			{
				menu[i]->scale = 1.2f;
				menu[i]->color = RGB(140, 100, 200);
			}
			else
			{
				menu[i]->scale = 1.0f;
				menu[i]->color = RGB(195,195,255);
			}
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			if (select == i)
			{
				menu[i]->scale = 1.2f;
				menu[i]->color = RGB(140, 100, 200);
			}
			else
			{
				menu[i]->scale = 1.0f;
				menu[i]->color = RGB(195, 195, 255);
			}
			menu[i]->position = menu[i]->positionE;
		}
	}
}

void MenuScene::Draw()
{
	spr->Draw(back, 0, 0, 0, 0, back->m_dwImageWidth, back->m_dwImageHeight);

	for (int i = 0; i<3; i++) {
		
		spr->Draw(image, menu[i]->position.x-10, menu[i]->position.y-10,0,0,image->m_dwImageWidth,image->m_dwImageHeight);

		GameDevice()->m_pFont->Draw(
			menu[i]->position.x+180, menu[i]->position.y+40, menu[i]->name.c_str(), 130*menu[i]->scale, menu[i]->color);
	}

}

Menu::Menu(VECTOR2 pos, std::string scenename, float scale)
{
	positionE = pos;
	name = scenename;
	this->scale = scale;
	color = RGB(200, 170, 255);
}
