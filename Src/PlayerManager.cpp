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

void PlayerManager::Update()
{
	positiveSum = 0;
	positive1p = ObjectManager::FindGameObject<Player>()->GetPositiveTime();
	for (auto pl : pls)
	{
		positiveSum += pl->GetPositiveTime();
	}
}

void PlayerManager::Draw()
{
	if (timer < startTime) {//ƒQ[ƒ€‚ªŽn‚Ü‚é‚Ü‚Å
		Ready();
	}

	CSprite spr;
	float gaugeMax = 800;
	float rate = positive1p / positiveSum;
	spr.DrawRect(275, 20, gaugeMax + 50, 30, RGB(100, 100, 100));
	spr.DrawRect(300, 25, gaugeMax * rate, 20, RGB(255, 100, 100));
	spr.DrawRect(300 + gaugeMax * rate, 25, gaugeMax * (1 - rate)+1, 20, RGB(100, 100, 255));
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

