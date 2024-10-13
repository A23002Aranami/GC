#pragma once
#include "Object3D.h"
#include "Player.h"
class PlayerPointer : public Object3D
{
public:
	PlayerPointer( Object3D* parent );
	
	void Update()override;
	void SetPosition(VECTOR3 Pos) { transform.position = Pos; }

private:
	Object3D* parent;
};