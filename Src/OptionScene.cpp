#include "OptionScene.h"

void OptionScene::Update()
{
	CDirectInput* DI = GameDevice()->m_pDI;

	if (DI->CheckKey(KD_TRG, DIK_SPACE))
	{
		SceneManager::ChangeScene("MenuScene");
	}
}

void OptionScene::Draw()
{
	GameDevice()->m_pFont->Draw(
		100 + 10, 500 + 10, "OPTION", 200, RGB(200, 170, 255));

	GameDevice()->m_pFont->Draw(
		100, 500, "OPTION", 200, RGB(255, 255, 255));

}
