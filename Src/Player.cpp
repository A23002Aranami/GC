#include "Player.h"
//#include "../Libs/Imgui/imgui.h"
#include "Dancer.h"
#include "Door.h"
#include "PlayerManager.h"

namespace { // このcpp以外では使えない
	static const float Gravity = 0.008f; // 重力加速度(正の値)
	// C++の定数定義（型が付く）
	static const float JumpPower = 0.25f;
	static const float RotationSpeed = 3.0f; // 回転速度(度)
	static const float DeadLine = -7.0f;//死亡する高さ
	static const float MoveSpeed = 0.1f;
	static const int MAX_AIRJUMP = 1;

	static const float MAX_ROTATION = 50.0f / 180.0f * XM_PI;

};

Player::Player()
{
	//number = menNum;
	//animator = new Animator(); // インスタンスを作成

	mesh = new CFbxMesh();
	colMesh = new CFbxMesh();
	/*
	mesh->LoadAnimation(aIdle, "Data/Player/Idle.anmx", true);//trueは繰り返す
	mesh->LoadAnimation(aRun, "Data/Player/Run.anmx", true);
	mesh->LoadAnimation(aAttack1,"Data/Player/attack1.anmx", false);//falseは繰り返さない
	mesh->LoadAnimation(aAttack2,"Data/Player/attack2.anmx", false);
	mesh->LoadAnimation(aAttack3,"Data/Player/attack3.anmx", false);
	animator->SetModel(mesh); // このモデルでアニメーションする
	animator->Play(aRun);
	animator->SetPlaySpeed(1.0f);
	*/
	transform.position = VECTOR3(0, 0, 0);
	transform.rotation = VECTOR3(0, 0, 0);
	state = sOnGround;
	Timer = 0;
	boundTime = 0.2;
	waitTime = 0;
	speedY = 0;
	airJump = 0;
	defKBR = 0.7f;
	KnockBackRate = defKBR;
	dangerTime = 0;
}

Player::~Player()
{
	//メッシュのデリート
	if (mesh != nullptr) {
		delete mesh;
		mesh = nullptr;
	}
	//判定用メッシュのデリート
	if (colMesh != nullptr) {
		delete colMesh;
		colMesh = nullptr;
	}
	/*
	if (animator != nullptr) {
		delete animator;
		animator = nullptr;
	}
	*/

}

void Player::Update()
{
	//animator->Update(); // 毎フレーム、Updateを呼ぶ

	switch (state) {
	case sOnGround:
		UpdateOnGround();
		break;
	case sJump:
		UpdateJump();
		break;
	case sStop:
		Stop();

	}



	//死亡処理Todo:死亡状態のUpdateを作成する（後回し）
	if (transform.position.y <= DeadLine)
	{
		//SceneManager::ChangeScene("ResultScene");
		ObjectManager::FindGameObject<PlayerManager>()->ReduceSurvivor(plNo);
		DestroyMe();
	}


}

void Player::Draw()
{
	char str[64];//文字列
	sprintf_s<64>(str, "%dP Y: %f", plNo, transform.position.y);//printfの形で文字列に入れてくれる

	GameDevice()->m_pFont->Draw(
		500, plNo * 50 + 50, str, 32, RGB(255, 255, 255));

	sprintf_s<64>(str, "%3.2f%%", (KnockBackRate - defKBR) / (2.0f - defKBR));
	GameDevice()->m_pFont->Draw(800, plNo * 50 + 50, str, 32, RGB(255, 255, 255));

	//Object3D::Draw();//継承元の関数を呼ぶ
	colMesh->Render(transform.matrix());
	CSprite spr;

	VECTOR3 Dir = XMVector3Normalize(CalcMoveVec(VECTOR3(0, 1, 0)));
	spr.DrawLine3D(transform.position, VECTOR3(transform.position.x, DeadLine, transform.position.z), RGB(160, 130, 130), 0.9f);
	spr.DrawLine3D(transform.position
		, transform.position + VECTOR3(Dir.x * 10, 0, Dir.z * 10), RGB(130, 160, 130), 0.9f);

}

void Player::Stop()
{
	waitTime++;
	if (waitTime >= wait)
	{
		waitTime = 0;
		state = (State)changeState;
	}
}

void Player::Stop(float time, int st)
{
	if (state != sStop)
		state = sStop;
	changeState = st;
	wait = time;

}


void Player::SetKeyBind(DWORD Forword, DWORD Back, DWORD Left, DWORD Right, DWORD LeanL, DWORD LeanR, DWORD Jump)
{
	inputForward = Forword;
	inputBack = Back;
	inputRight = Right;
	inputLeft = Left;
	inputLeanL = LeanL;
	inputLeanR = LeanR;
	inputJump = Jump;
}

DWORD Player::GetKeyBind(char key)
{
	switch (key)
	{
	case 'F':
		return inputForward;
		break;
	case 'B':
		return inputBack;
		break;
	case 'L':
		return inputLeft;
		break;
	case 'R':
		return inputRight;
		break;

	default:
		break;
	}
}

VECTOR3 Player::CalcMoveVec(VECTOR3 forward)
{
	MATRIX4X4 rotX = XMMatrixRotationX(transform.rotation.x); // Xの回転行列
	MATRIX4X4 rotY = XMMatrixRotationY(transform.rotation.y); // Yの回転行列
	MATRIX4X4 rotZ = XMMatrixRotationZ(transform.rotation.z); // Zの回転行列

	return (forward * rotZ * rotX * rotY);
}

bool Player::ThrouthCheckStoM(Object3D* obj, SphereCollider coll, VECTOR3* push, VECTOR3 speed, int per)
{

	VECTOR3 v = VECTOR3(speed.x / per, speed.y / per, speed.z / per);//速度を分割する
	VECTOR3 ret;//押し出すベクトル
	VECTOR3 pos = transform.position;

	//分割数に合わせて処理を繰り返す
	for (int i = 0; i < per; i++)
	{

		pos += v;

		if (obj->HitSphereToMesh(coll, &ret)) {//接触していたら
			pos += ret;
			*push = pos - transform.position;
			return true;
		}


	}

	*push = VECTOR3(0, 0, 0);//押し返す量を０として返す
	return false;

}

void Player::LoadMesh(std::string meshName)
{
	std::string folder;
	folder = "Data/Mochi/";
	mesh->Load((folder + meshName).c_str());
}
void Player::LoadColMesh(std::string meshName)
{
	std::string folder;
	folder = "Data/Mochi/";
	colMesh->Load((folder + meshName).c_str());
}


SphereCollider Player::Collider()
{
	SphereCollider col;
	col.center = transform.position;
	col.radius = 0.5f;
	return col;
}

void Player::KnockBack(Player* atacker, Player* difender)
{
	float roteA = fabs(atacker->Rotation().x);
	float roteD = fabs(difender->Rotation().x);

	if (roteA > roteD) {//攻撃側の方が傾いている場合
		difender->AddKBR(0.4f);//相手の吹っ飛び率を増やす
	}
	else if (roteA == roteD)//攻撃側と受け側の傾きが同じ場合
	{
		difender->AddKBR(0.3f);//相手の吹っ飛び率を増やす
	}
	else//受け側の方が傾いている場合
	{
		difender->AddKBR(0.1f);//相手の吹っ飛び率を増やす
	}

	difender->SetVec(atacker->GetVec() * GetKBR());
	atacker->SetVec(VECTOR3(0, 0, 0));
}

void Player::Input()
{
	CDirectInput* DI = GameDevice()->m_pDI;

	if (DI->CheckKey(KD_DAT, inputForward)
		&& transform.rotation.x <= MAX_ROTATION) {//前ボタン

		//animator->MergePlay(aRun);

		transform.rotation.x += RotationSpeed / 180.0f * XM_PI / 3;
	}
	else if (DI->CheckKey(KD_DAT, inputBack)) {//後ボタン
		transform.rotation.x -= RotationSpeed / 180.0f * XM_PI / 3;
	}
	if (DI->CheckKey(KD_DAT, inputLeft)) {//左ボタン
		transform.rotation.y -= RotationSpeed / 180.0f * XM_PI;
	}
	if (DI->CheckKey(KD_DAT, inputRight)) {//右ボタン
		transform.rotation.y += RotationSpeed / 180.0f * XM_PI;
	}
}

void Player::UpdateOnGround()
{
	CDirectInput* DI = GameDevice()->m_pDI;

	Timer += SceneManager::DeltaTime();
	Input();

	if (transform.rotation.x > MAX_ROTATION)
	{
		transform.rotation.x = MAX_ROTATION;
	}
	if (transform.rotation.x < -MAX_ROTATION)
	{
		transform.rotation.x = -MAX_ROTATION;
	}

	/*
	//リーンの機能は必要ないため削除	2024.8.15
	if (DI->CheckKey(KD_DAT, inputLeanL))//左リーンボタン
	{
		transform.rotation.z += RotationSpeed / 180.0f * XM_PI;
	}
	if (DI->CheckKey(KD_DAT, inputLeanR))//右リーンボタン
	{
		transform.rotation.z -= RotationSpeed / 180.0f * XM_PI;
	}

	*/
	if (DI->CheckKey(KD_TRG, inputJump) || Timer >= boundTime) {//ジャンプボタン
		VECTOR3 forward = VECTOR3(0, JumpPower, 0); // 回転してない時の移動量
		speed = CalcMoveVec(forward); // キャラの向いてる方への移動量

		//ジャンプのタイマーリセット
		Timer = 0;
		state = sJump;
	}




	if (DI->CheckKey(KD_TRG, DIK_R))//「R」
	{
		SceneManager::ChangeScene("ResultScene");
	}

}

void Player::UpdateJump()
{
	CDirectInput* DI = GameDevice()->m_pDI;

	Input();

	//空中ジャンプ
	if (DI->CheckKey(KD_TRG, inputJump) && airJump < MAX_AIRJUMP) {//ジャンプボタン

		VECTOR3 forward = VECTOR3(0, JumpPower, 0); // 回転してない時の移動量
		speed = CalcMoveVec(forward); // キャラの向いてる方への移動量
		//speed.y = vec.y;

		airJump++;
	}

	//線分で地面との判定をするため
	VECTOR3 begin;//線分の始点
	VECTOR3 end;//線分の終点

	begin = transform.position;

	//降下処理
	transform.position += speed;
	speed.y -= Gravity;

	end = transform.position;



	//指定されたタグのオブジェクトを探索する
	std::list<Object3D*> objs = ObjectManager::FindGameObjectsWithTag<Object3D>("STAGEOBJ");

	for (auto obj : objs)
	{
		/*
		//地面とホッピングの判定処理
		VECTOR3 hit;
		if (obj->HitLineToMesh(begin, end, &hit))
		{
			transform.position = hit + VECTOR3(0,0.01f,0);
			airJump = 0;
			state = sOnGround;
		}

		*/


#if 1
		//地面とホッピングの判定処理
		float radius = 0.35f;//スフィアが小さすぎると判定でエラーが起きてしまうので注意
		SphereCollider coll(transform.position + VECTOR3(0, radius, 0), radius);

		VECTOR3 push;

		if (ThrouthCheckStoM(obj, coll, &push, speed, 10))//判定処理細分化
		{
			transform.position += push;
			airJump = 0;
			state = sOnGround;//ステートを地面判定にする

		}

#endif

		//ステージ端で滑らかに落ちてすり抜けないようにするための処理
		radius = 0.5f;
		SphereCollider bodyColl(transform.position + VECTOR3(0, radius + 0.2f, 0), radius);


		if (obj->HitSphereToMesh(bodyColl, &push))//ステージオブジェクトのポリゴンがスフィアコライダーに当たった時
		{
			//当たった時に反発する距離を食い込んだ二倍の量に
			transform.position += push * 2;
			speed.y = 0.0f;
		}

	}


	//プレイヤー同士の接触判定
	std::list<Player*> pls = ObjectManager::FindGameObjects<Player>();

	for (auto pl : pls)
	{
		if (pl->plNo != this->plNo)
		{

			float radius = 0.5f;
			SphereCollider coll(transform.position + VECTOR3(0, radius + 0.2f, 0), radius);
			VECTOR3 push;
			VECTOR3 hit;


			VECTOR3 length = transform.position - pl->Position();

			//if (ThrouthCheckStoM(pl, coll, &push, speed, 1000))
			if (length.Length() < (radius * 2))
			{
				//ヒットストップ
				int hitStop = 5;//20フレーム
				Stop(hitStop, sJump);
				pl->Stop(hitStop, sJump);

				//接触した際にある程度離す処理dd
				VECTOR3 toMe = transform.position - pl->Position();
				push = toMe / 2;

				transform.position += push;
				pl->SetPosition(pl->Position() - push);

				//自分の速度のほうが早かった場合
				if (speed.Length() > pl->GetVec().Length())
				{
					KnockBack(this, pl);
				}
				//相手の速度のほうが早かった場合
				else if (speed.Length() < pl->GetVec().Length())
				{
					KnockBack(pl, this);
				}
				//速度が同じだった場合
				else
				{
					speed = VECTOR3();
					pl->SetVec(VECTOR3());
				}



			}
		}
	}
}
