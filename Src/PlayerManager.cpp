#include "PlayerManager.h"
#include "Score.h"

PlayerManager::PlayerManager(int num)
{
	startTime = 180;
	timer = 0;

	pls =  ObjectManager::FindGameObjects<Player>();
	for (auto pl : pls)
	{
		pl->Stop(startTime, pl->sJump);
	}
	for (int i = 0; i < num; i++)
	{
		survivor.push_back(i+1);
	}

	

}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::Draw()
{
	if (timer < startTime) {//ƒQ[ƒ€‚ªŽn‚Ü‚é‚Ü‚Å
		Ready();
	}
}

void PlayerManager::ReduceSurvivor( int plNo )
{
	int removeNo = plNo - 1;
	survivor.erase(survivor.begin() + removeNo);

	if (survivor.size() <= 1)
	{
		for (auto winner : survivor)
		{
			ObjectManager::FindGameObject<Score>()->SetWinner(winner);
		}

		SceneManager::ChangeScene("ResultScene");
	}
}

void PlayerManager::Ready()
{
	timer++;
	int sec = 60;

	char str[64];//•¶Žš—ñ
	sprintf_s<64>(str, "%d", (startTime - timer) / sec + 1);
	GameDevice()->m_pFont->Draw(
		610, 260, str, 300, RGB(200, 170, 255));

	sprintf_s<64>(str, "%d", (startTime - timer) / sec + 1);
	GameDevice()->m_pFont->Draw(
		600, 250, str, 300, RGB(255, 255, 255));
}

