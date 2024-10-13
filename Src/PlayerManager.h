#pragma once
#include "GameObject.h"
#include "Player.h"
#include "camera.h"

class PlayerManager : public GameObject
{
public:

	PlayerManager(int num);//プレイヤー数を引数にする
	~PlayerManager();

	void Update()override;
	void Draw()override;

	void ReduceSurvivor( int plNo );
	void Ready();

private:
	std::list<Player*> pls;
	std::vector<int> survivor;
	int startTime;//ゲームが始まる時間
	int timer;
	float rate;
	float scale;
	float positiveSum;
	float positive1p;
};