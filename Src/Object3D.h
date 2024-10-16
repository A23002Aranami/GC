#pragma once
#include "GameObject.h"
#include "FbxMesh.h"
#include "MeshCollider.h"

class Transform {
public:
	VECTOR3 position;
	VECTOR3 rotation;
	VECTOR3 scale;
	Transform() {
		position = VECTOR3(0, 0, 0);
		rotation = VECTOR3(0, 0, 0);
		scale = VECTOR3(1, 1, 1);
		parent = nullptr;
	}
	const MATRIX4X4 matrix() {
		MATRIX4X4 scaleM = XMMatrixScaling(
			scale.x, scale.y, scale.z);
		MATRIX4X4 rotX = XMMatrixRotationX(
			rotation.x);
		MATRIX4X4 rotY = XMMatrixRotationY(
			rotation.y);
		MATRIX4X4 rotZ = XMMatrixRotationZ(
			rotation.z);
		MATRIX4X4 trans = XMMatrixTranslation(
			position.x, position.y, position.z);
		return scaleM * rotZ * rotX * rotY * trans;


	}

	
	//親オブジェクトをセットする
	void SetParent(Object3D* parent) { this->parent = parent; }
	Object3D* GetParent() { return parent; }
private:
	Object3D* parent;
};

class SphereCollider {
public:
	VECTOR3 center;
	float radius;
	SphereCollider() {
		SphereCollider(VECTOR3(0, 0, 0), 0.0f);
	}
	/// <summary>
	/// スフィアコライダーの情報
	/// </summary>
	/// <param name="centerPos">球の中心座標</param>
	/// <param name="r">球の半径</param>
	SphereCollider(VECTOR3 centerPos, float r)
	{
		center = centerPos;
		radius = r;
	}
};

class Object3D : public GameObject {
public:
	Object3D();
	virtual ~Object3D();
	virtual void Update() override;
	virtual void Draw() override;

	const VECTOR3 Position() {
		return transform.position;
	};
	const VECTOR3 Rotation() {
		return transform.rotation;
	};
	const VECTOR3 Scale() {
		return transform.scale;
	};

	void SetPosition(const VECTOR3& pos);
	void SetPosition(float x, float y, float z);
	void SetRotation(const VECTOR3& pos);
	void SetRotation(float x, float y, float z);
	void SetScale(const VECTOR3& pos);
	void SetScale(float x, float y, float z);
	void SetCsvLine(int line);
	/// <summary>
	/// フルパスの名前から、メッシュをロード
	/// </summary>
	/// <param name="meshName"></param>
	void LoadMesh(std::string meshName);
	virtual SphereCollider Collider();

	/// <summary>
	/// 球とメッシュの当たり判定をする
	/// 当たった場合にのみ、pushに押し返す場所を返す
	/// </summary>
	/// <param name="sphere">球体</param>
	/// <param name="push">押し返す場所を格納する場所</param>
	/// <returns>当たった場合にtrue</returns>
	virtual bool HitSphereToMesh(const SphereCollider& sphere, VECTOR3* push = nullptr);

	/// <summary>
	/// 直線とメッシュの当たり判定をする
	/// 当たった場合は、当たった座標を返す
	/// </summary>
	/// <param name="from">直線の始点</param>
	/// <param name="to">直線の終点</param>
	/// <param name="hit">交点を格納する場所</param>
	/// <returns>当たった場合にtrue</returns>
	virtual bool HitLineToMesh(const VECTOR3& from, const VECTOR3& to, VECTOR3* hit = nullptr);

	/// <summary>
	/// 球と球の当たり判定をする
	/// 自分の球は、Collider()で取得する
	/// </summary>
	/// <param name="target">相手の球</param>
	/// <param name="withY">falseにするとYの座標差を無視する</param>
	/// <returns>重なり量</returns>
	virtual float HitSphereToSphere(const SphereCollider& target, bool withY=true);
protected:
	CFbxMesh* mesh;
	MeshCollider* meshCol;
	Transform transform;
	int csvLine;//オブジェクトの情報を指定するcsvの行を保持
};