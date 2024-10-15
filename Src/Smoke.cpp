#include "Smoke.h"

Smoke::Smoke(int time, Object3D* parent, VECTOR3 rotation )
{
	mesh = new CFbxMesh();
	mesh->Load("Data/Effect/Smoke.mesh");
	disTime = time;
	timer = 0;

	defScale = VECTOR3(2.5, 2, 2.5);
	
	transform.position = parent->Position();//êŠ‚ğƒvƒŒƒCƒ„[‚Ì‘«Œ³‚Éİ’è
	
	defRot = rotation;
	rot = VECTOR3(0, 0, 0);

	

}

void Smoke::Update()
{
	if (transform.rotation.x != 0)
	{
		transform.position.y += 2;
	}
	timer++;

	float timeRate = (float)timer / ((float)disTime/2);

	if (timeRate > 1.0f)
	{
		timeRate = 1.0f;
	}

	transform.scale = defScale * timeRate;

	rot.y -= -5 * DegToRad;

	
	transform.rotation = rot;//c²‰ñ“]‚µ‚È‚ª‚ç•\¦

	if (timer > disTime)
	{
		DestroyMe();
	}
}

void Smoke::Draw()
{
	MATRIX4X4 mat;

	MATRIX4X4 Rot = XMMatrixRotationRollPitchYawFromVector(defRot);

	MATRIX4X4 scaleM = XMMatrixScaling(
		transform.scale.x, transform.scale.y, transform.scale.z);
	MATRIX4X4 rotX = XMMatrixRotationX(
		transform.rotation.x);
	MATRIX4X4 rotY = XMMatrixRotationY(
		transform.rotation.y);
	MATRIX4X4 rotZ = XMMatrixRotationZ(
		transform.rotation.z);
	MATRIX4X4 trans = XMMatrixTranslation(
		transform.position.x, transform.position.y, transform.position.z);
	mat = scaleM * rotZ * rotX * rotY * Rot *  trans;



	mesh->Render(mat);
}
