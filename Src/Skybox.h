#pragma once
#include "Object3D.h"
#include "camera.h"
class SkyBox : public Object3D
{
public:
	SkyBox();
	void Update()override;
	void LoadMesh(std::string meshName);
	
private:
	float scale;
	
};