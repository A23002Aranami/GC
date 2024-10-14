#include "Smoke.h"

Smoke::Smoke(int time, Object3D* parent, VECTOR3 rotation )
{
	mesh = new CFbxMesh();
	mesh->Load("Data/Effect/Smoke.mesh");
	disTime = time;
	timer = 0;

	defScale = VECTOR3(2.5, 2, 2.5);
	
	transform.position = parent->Position();//êŠ‚ðƒvƒŒƒCƒ„[‚Ì‘«Œ³‚ÉÝ’è
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
	transform.rotation = rot * Rot;//cŽ²‰ñ“]‚µ‚È‚ª‚ç•\Ž¦

	if (timer > disTime)
	{
		DestroyMe();
	}
}
