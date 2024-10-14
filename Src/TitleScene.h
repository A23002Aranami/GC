#pragma once
#include "SceneBase.h"

class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;
private: // クラスのメンバー変数はprivateにする
	int positionX;
	int speedX;
	CSpriteImage* LogoImage;
	CSprite* spr;
};
