#include "PlayerManager.h"
#include "Score.h"

PlayerManager::PlayerManager(int num)
{
	for (int i = 0; i < num; i++)
	{
		survivor.push_back(i+1);
	}
}

PlayerManager::~PlayerManager()
{
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

