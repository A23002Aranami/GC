#pragma once
#include "GameObject.h"

class Score : public GameObject
{
public:

	Score();
	~Score();
	void Update()override;
	void Draw()override;
	int GetScore() { return score; }


	//スコアリセット関数
	void Clear()
	{
		score = 0;
	}
	//スコア加算関数
	void AddScore(int val)
	{
		score += val;
	}

	//勝者を設定する
	void SetWinner(int no) { winner = no; }

	int GetWinner() { return winner; };

private:
	int score;//スコア
	int winner;

};