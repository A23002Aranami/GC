#pragma once
#include "Object3D.h"

class Smoke : public Object3D
{
public:
	Smoke(int time,Object3D* parent, VECTOR3 rotation);

	void Update()override;
	void Draw()override;
private:
	int timer;
	int disTime;//表示時間上限
	VECTOR3 defScale;
	VECTOR3 defRot;
	VECTOR3 rot;

};