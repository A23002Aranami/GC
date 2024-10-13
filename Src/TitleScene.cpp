#include "TitleScene.h"
#include "GameMain.h"

TitleScene::TitleScene()
{
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
	GameDevice()->m_pFont->Draw(
		500, 200, "HOPPING", 100, RGB(255, 255, 255));
	GameDevice()->m_pFont->Draw(
		200, 400, "PUSH SPACE TO PLAY", 100, RGB(255, 255, 255));
}