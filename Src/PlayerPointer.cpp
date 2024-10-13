#include "PlayerPointer.h"

PlayerPointer::PlayerPointer( Object3D* parent )
{

	mesh = new CFbxMesh();
	mesh->Load("Data/Mochi/Point1P.mesh");
	this->parent = parent;
}

void PlayerPointer::Update()
{

	VECTOR3 parentPos = parent->Position();//親のポジション
	VECTOR3 begin = parentPos;
	VECTOR3 end = VECTOR3(0,-7,0) + VECTOR3( parentPos.x,0,parentPos.z);
	VECTOR3 hit;
	std::list<Object3D*> stageObj = ObjectManager::FindGameObjectsWithTag<Object3D>("STAGEOBJ");
	for (auto obj : stageObj) {
		if (obj->HitLineToMesh(begin, end, &hit))
		{
			transform.position = hit;
			break;
		}
		else
		{
			transform.position = VECTOR3(parentPos.x, 0, parentPos.z);
		}
	}

	if (parent->Rotation().x >= 0)
	{
		transform.rotation.y = parent->Rotation().y;
	}
	else
	{
		transform.rotation.y = parent->Rotation().y + 180 * DegToRad;
	}
	



}
