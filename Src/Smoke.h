#pragma once
#include "Object3D.h"

class Smoke : public Object3D
{
public:
	Smoke(int time,Object3D* parent, VECTOR3 rotation);

	void Update()override;
private:
	int timer;
	int disTime;//�\�����ԏ��
	VECTOR3 defScale;
	VECTOR3 defRot;
	VECTOR3 rot;

};