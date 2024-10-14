#include "TitleScene.h"
#include "GameMain.h"

TitleScene::TitleScene()
{
	LogoImage = new CSpriteImage(GameDevice()->m_pShader,"Data/Image/TITLE.png");
	spr = new CSprite();
	positionX = 0;
	speedX = 1;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	positionX += speedX;
	if (positionX >= 60) {
		speedX *= -1;
	}
	else {
		if (positionX <= 0) {
			speedX *= -1;
		}
	}
	if (GameDevice()->m_pDI->
			CheckKey(KD_TRG, DIK_SPACE)) {
		SceneManager::ChangeScene("MenuScene");
	}
}

void TitleScene::Draw()
{

	int x = LogoImage->m_dwImageWidth;
	int y = LogoImage->m_dwImageHeight;


	GameDevice()->m_pFont->Draw(
		380, 550, "PUSH SPACE TO PLAY", 64, RGB(255, 255, 255));

	spr->Draw(LogoImage,200,0,0,0,x,y);
}