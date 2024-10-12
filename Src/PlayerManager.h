#pragma once
#include "GameObject.h"

class PlayerManager : public GameObject
{
public:

	PlayerManager(int num);//プレイヤー数を引数にする
	~PlayerManager();

	void ReduceSurvivor( int plNo );

private:
	std::vector<int> survivor;

};