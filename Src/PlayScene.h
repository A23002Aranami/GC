#pragma once
#include "SceneBase.h"

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
	int players;//プレイヤーの人数(人数は１から)
};
