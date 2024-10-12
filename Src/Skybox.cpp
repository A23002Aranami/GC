#include "Skybox.h"


SkyBox::SkyBox()
{
	mesh = new CFbxMesh();
	scale = 2.0f;
	
}

void SkyBox::Update()
{
	transform.scale = VECTOR3(1,1,1)*scale;
	Camera* cam = ObjectManager::FindGameObject<Camera>();
	transform.position = cam->Position() + VECTOR3(0,0,0);

}



void SkyBox::LoadMesh(std::string meshName)
{
	std::string folder;
	folder = "Data/Skybox/";
	mesh->Load((folder + meshName).c_str());
}
