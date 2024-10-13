#include "Player.h"
//#include "../Libs/Imgui/imgui.h"

#include "PlayerManager.h"
#include "PlayerPointer.h"

namespace { // ����cpp�ȊO�ł͎g���Ȃ�
	static const float Gravity = 0.008f; // �d�͉����x(���̒l)
	// C++�̒萔��`�i�^���t���j
	static const float JumpPower = 0.25f;
	static const float RotationSpeed = 3.0f; // ��]���x(�x)
	static const float DeadLine = -7.0f;//���S���鍂��
	static const float MoveSpeed = 0.1f;
	static const int MAX_AIRJUMP = 1;
	static const DWORD color[] =
	{
		RGB(0,0,0),
		RGB(255,100,100),
		RGB(100,100,255)
	};
	static const float MAX_ROTATION = 50.0f / 180.0f * XM_PI;

};

Player::Player()
{
	//number = menNum;
	//animator = new Animator(); // �C���X�^���X���쐬

	mesh = new CFbxMesh();
	colMesh = new CFbxMesh();
	/*
	mesh->LoadAnimation(aIdle, "Data/Player/Idle.anmx", true);//true�͌J��Ԃ�
	mesh->LoadAnimation(aRun, "Data/Player/Run.anmx", true);
	mesh->LoadAnimation(aAttack1,"Data/Player/attack1.anmx", false);//false�͌J��Ԃ��Ȃ�
	mesh->LoadAnimation(aAttack2,"Data/Player/attack2.anmx", false);
	mesh->LoadAnimation(aAttack3,"Data/Player/attack3.anmx", false);
	animator->SetModel(mesh); // ���̃��f���ŃA�j���[�V��������
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
	positiveTime = 0;

	positive = false;

	new PlayerPointer(this);
}

Player::~Player()
{
	//���b�V���̃f���[�g
	if (mesh != nullptr) {
		delete mesh;
		mesh = nullptr;
	}
	//����p���b�V���̃f���[�g
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
	//animator->Update(); // ���t���[���AUpdate���Ă�

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



	//���S����Todo:���S��Ԃ�Update���쐬����i��񂵁j
	if (transform.position.y <= DeadLine)
	{
		//SceneManager::ChangeScene("ResultScene");
		ObjectManager::FindGameObject<PlayerManager>()->ReduceSurvivor(plNo);
		DestroyMe();
	}


}

void Player::Draw()
{
	//Object3D::Draw();//�p�����̊֐����Ă�
	colMesh->Render(transform.matrix());

	char str[64];//������
	sprintf_s<64>(str, "%dP Y: %f", plNo, transform.position.y);//printf�̌`�ŕ�����ɓ���Ă����

	VECTOR3 disPos = XMVector3Project(
		transform.position + VECTOR3(-0.25f, 2.0f, 0), 0, 0,
		WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 1.0f,
		GameDevice()->m_mProj, GameDevice()->m_mView, XMMatrixIdentity()
	);

	sprintf_s<64>(str, "%dP", plNo);
	GameDevice()->m_pFont->Draw(disPos.x+2, disPos.y+2, str, 32, RGB(150, 150, 150));

	sprintf_s<64>(str, "%dP",plNo);
	GameDevice()->m_pFont->Draw(disPos.x, disPos.y , str, 32, color[plNo]);


	
	CSprite spr;

	/*
	VECTOR3 Dir = XMVector3Normalize(CalcMoveVec(VECTOR3(0, 1, 0)));
	spr.DrawLine3D(transform.position, VECTOR3(transform.position.x, DeadLine, transform.position.z), RGB(160, 130, 130), 0.9f);
	spr.DrawLine3D(transform.position
		, transform.position + VECTOR3(Dir.x * 10, 0, Dir.z * 10), RGB(130, 160, 130), 0.9f);
	*/

	spr.DrawRect(plNo * 500 - 25 - 250, 600 - 2 , 300, 100,RGB(100,100,100),0.6f);
	GameDevice()->m_pFont->Draw(
		plNo * 500-250, 550, str, 32, color[plNo]);

	if(positive){
	GameDevice()->m_pFont->Draw(
		plNo * 500 - 200, 550, "POSITIVE", 32, RGB(255, 150, 100));

	}

	sprintf_s<64>(str, "%3.0f%%", (KnockBackRate - defKBR) / (2.0f - defKBR) * 100);
	GameDevice()->m_pFont->Draw(plNo * 500+5-250, 600+5, str, 100, RGB(255, 150, 100));

	sprintf_s<64>(str, "%3.0f%%", (KnockBackRate - defKBR) / (2.0f - defKBR) * 100);
	GameDevice()->m_pFont->Draw(plNo * 500-250, 600, str, 100, RGB(255, 255, 255));


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
	MATRIX4X4 rotX = XMMatrixRotationX(transform.rotation.x); // X�̉�]�s��
	MATRIX4X4 rotY = XMMatrixRotationY(transform.rotation.y); // Y�̉�]�s��
	MATRIX4X4 rotZ = XMMatrixRotationZ(transform.rotation.z); // Z�̉�]�s��

	return (forward * rotZ * rotX * rotY);
}

bool Player::ThrouthCheckStoM(Object3D* obj, SphereCollider coll, VECTOR3* push, VECTOR3 speed, int per)
{

	VECTOR3 v = VECTOR3(speed.x / per, speed.y / per, speed.z / per);//���x�𕪊�����
	VECTOR3 ret;//�����o���x�N�g��
	VECTOR3 pos = transform.position;

	//�������ɍ��킹�ď������J��Ԃ�
	for (int i = 0; i < per; i++)
	{

		pos += v;

		if (obj->HitSphereToMesh(coll, &ret)) {//�ڐG���Ă�����
			pos += ret;
			*push = pos - transform.position;
			return true;
		}


	}

	*push = VECTOR3(0, 0, 0);//�����Ԃ��ʂ��O�Ƃ��ĕԂ�
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

	if (roteA > roteD) {//�U�����̕����X���Ă���ꍇ
		difender->AddKBR(0.3f);//����̐�����ї��𑝂₷
	}
	else if (roteA == roteD)//�U�����Ǝ󂯑��̌X���������ꍇ
	{
		difender->AddKBR(0.2f);//����̐�����ї��𑝂₷
	}
	else//�󂯑��̕����X���Ă���ꍇ
	{
		difender->AddKBR(0.1f);//����̐�����ї��𑝂₷
	}

	difender->SetVec(atacker->GetVec() * GetKBR());
	atacker->SetVec(VECTOR3(0, 0, 0));
}

void Player::Input()
{
	CDirectInput* DI = GameDevice()->m_pDI;

	if (DI->CheckKey(KD_DAT, inputForward)
		&& transform.rotation.x <= MAX_ROTATION) {//�O�{�^��

		//animator->MergePlay(aRun);

		transform.rotation.x += RotationSpeed / 180.0f * XM_PI / 3;
	}
	else if (DI->CheckKey(KD_DAT, inputBack)) {//��{�^��
		transform.rotation.x -= RotationSpeed / 180.0f * XM_PI / 3;
	}
	if (DI->CheckKey(KD_DAT, inputLeft)) {//���{�^��
		transform.rotation.y -= RotationSpeed / 180.0f * XM_PI;
	}
	if (DI->CheckKey(KD_DAT, inputRight)) {//�E�{�^��
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
	//���[���̋@�\�͕K�v�Ȃ����ߍ폜	2024.8.15
	if (DI->CheckKey(KD_DAT, inputLeanL))//�����[���{�^��
	{
		transform.rotation.z += RotationSpeed / 180.0f * XM_PI;
	}
	if (DI->CheckKey(KD_DAT, inputLeanR))//�E���[���{�^��
	{
		transform.rotation.z -= RotationSpeed / 180.0f * XM_PI;
	}

	*/
	if (DI->CheckKey(KD_TRG, inputJump) || Timer >= boundTime) {//�W�����v�{�^��
		VECTOR3 forward = VECTOR3(0, JumpPower, 0); // ��]���ĂȂ����̈ړ���
		speed = CalcMoveVec(forward); // �L�����̌����Ă���ւ̈ړ���

		//�W�����v�̃^�C�}�[���Z�b�g
		Timer = 0;
		state = sJump;
	}




	if (DI->CheckKey(KD_TRG, DIK_R))//�uR�v
	{
		SceneManager::ChangeScene("ResultScene");
	}

}

void Player::UpdateJump()
{
	CDirectInput* DI = GameDevice()->m_pDI;

	Input();

	int maxAirJump;

	if (positive)
	{
		maxAirJump = 2;
	}
	else
	{
		maxAirJump = 1;
	}
	//�󒆃W�����v
	if (DI->CheckKey(KD_TRG, inputJump) && airJump < maxAirJump ) {//�W�����v�{�^��

		VECTOR3 forward = VECTOR3(0, JumpPower, 0); // ��]���ĂȂ����̈ړ���
		speed = CalcMoveVec(forward); // �L�����̌����Ă���ւ̈ړ���
		//speed.y = vec.y;

		airJump++;
	}

	//�����Œn�ʂƂ̔�������邽��
	VECTOR3 begin;//�����̎n�_
	VECTOR3 end;//�����̏I�_

	begin = transform.position;

	//�~������
	transform.position += speed;
	speed.y -= Gravity;

	end = transform.position;



	//�w�肳�ꂽ�^�O�̃I�u�W�F�N�g��T������
	std::list<Object3D*> objs = ObjectManager::FindGameObjectsWithTag<Object3D>("STAGEOBJ");

	for (auto obj : objs)
	{
		
#if 1
		//�n�ʂƃz�b�s���O�̔��菈��
		float radius = 0.35f;//�X�t�B�A������������Ɣ���ŃG���[���N���Ă��܂��̂Œ���
		SphereCollider coll(transform.position + VECTOR3(0, radius, 0), radius);

		VECTOR3 push;

		if (ThrouthCheckStoM(obj, coll, &push, speed, 10))//���菈���ו���
		{
			transform.position += push*3;
			airJump = 0;
			state = sOnGround;//�X�e�[�g��n�ʔ���ɂ���

		}

#endif

		//�X�e�[�W�[�Ŋ��炩�ɗ����Ă��蔲���Ȃ��悤�ɂ��邽�߂̏���
		radius = 0.8f;
		SphereCollider bodyColl(transform.position + VECTOR3(0, radius + 0.2f, 0), radius);


		if (obj->HitSphereToMesh(bodyColl, &push))//�X�e�[�W�I�u�W�F�N�g�̃|���S�����X�t�B�A�R���C�_�[�ɓ���������
		{
			//�����������ɔ������鋗����H�����񂾓�{�̗ʂ�
			transform.position += push * 2;
			speed.y = 0.0f;
		}

	}


	//�v���C���[���m�̐ڐG����
	std::list<Player*> pls = ObjectManager::FindGameObjects<Player>();

	for (auto pl : pls)
	{
		if (pl->plNo != this->plNo)
		{
			if (fabs(transform.rotation.x) > fabs(pl->Rotation().x))
			{
				positiveTime++;
			}

			if (positiveTime > pl->GetPositiveTime())
			{
				positive = true;
			}
			else
			{
				positive = false;
			}
			
			float radius = 0.5f;
			SphereCollider coll(transform.position + VECTOR3(0, radius + 0.2f, 0), radius);
			VECTOR3 push;
			VECTOR3 hit;


			VECTOR3 length = transform.position - pl->Position();

			//if (ThrouthCheckStoM(pl, coll, &push, speed, 1000))
			if (length.Length() < (radius * 2))
			{
				//�q�b�g�X�g�b�v
				int hitStop = 5;//20�t���[��
				Stop(hitStop, sJump);
				pl->Stop(hitStop, sJump);

				//�ڐG�����ۂɂ�����x��������dd
				VECTOR3 toMe = transform.position - pl->Position();
				push = toMe / 2;

				transform.position += push;
				pl->SetPosition(pl->Position() - push);

				//�����̑��x�̂ق������������ꍇ
				if (speed.Length() > pl->GetVec().Length())
				{
					KnockBack(this, pl);
				}
				//����̑��x�̂ق������������ꍇ
				else if (speed.Length() < pl->GetVec().Length())
				{
					KnockBack(pl, this);
				}
				//���x�������������ꍇ
				else
				{
					speed = VECTOR3();
					pl->SetVec(VECTOR3());
				}



			}
		}
	}
}
