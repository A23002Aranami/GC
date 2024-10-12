#pragma once
//camera.h
#include"Object3D.h"

class Camera : public Object3D
{
public:
	Camera();
	~Camera();

	void Update() override;
	void Draw() override;
	MATRIX4X4 Matrix() { return transform.matrix(); }

private:
	VECTOR3 lookPosition;
	
	float distance;//２キャラの距離
	VECTOR3 Look;
	VECTOR3 CamPos;

	int viewType = 0; //視点切替の番号
	
	float changeTime;
	VECTOR3 changePosStart;//視点移動の開始点
	VECTOR3 changePosGoal;//視点移動の終了点
	VECTOR3 changeLookStart;//視点移動の開始点
	VECTOR3 changeLookGoal;//視点移動の終了点
};
