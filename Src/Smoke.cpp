#include "Smoke.h"

Smoke::Smoke(int time, Object3D* parent, VECTOR3 rotation )
{
	mesh = new CFbxMesh();
	mesh->Load("Data/Effect/Smoke.mesh");
	disTime = time;
	timer = 0;

	defScale = VECTOR3(2.5, 2, 2.5);
	
	transform.position = parent->Position();//場所をプレイヤーの足元に設定
	defRot = rotation;
	rot = VECTOR3(0, 0, 0);

	

}

void Smoke::Update()
{
	timer++;

	float timeRate = (float)timer / ((float)disTime/2);

	if (timeRate > 1.0f)
	{
		timeRate = 1.0f;
	}

	transform.scale = defScale * timeRate;

	rot.y -= -5 * DegToRad;
	MATRIX4X4 Rot = XMMatrixRotationRollPitchYawFromVector(defRot);
	transform.rotation = rot * Rot;//縦軸回転しながら表示

	if (timer > disTime)
	{
		DestroyMe();
	}
}
