#pragma once
// Player.h
#include "Object3D.h"
//#include "Animator.h"

class Player : public Object3D {
public:
	Player();
	~Player();
	void Update() override;
	void Draw()override;
	void Stop();
	void Stop(float time, int st);

	//自分が何番目のプレイヤーかを判定するための数値を設定
	void SetPlNo(int no) { plNo = no; }

	/// <summary>
	/// キーバインドを設定するための関数
	/// </summary>
	/// <param name="前に移動するためのキー設定"></param>
	/// <param name="後ろに移動するためのキー設定"></param>
	/// <param name="右に移動するためのキー設定"></param>
	/// <param name="左に移動するためのキー設定"></param>
	/// <param name="ジャンプするためのキー設定"></param>
	void SetKeyBind(DWORD inputForword, DWORD inputBack, DWORD inputLeft, DWORD inputRight, DWORD LeanL, DWORD LeanR, DWORD inputJump);
	DWORD GetKeyBind(char key);//設定してあるキーを取得する



	/// <summary>
	/// 進行方向のベクトルを求める計算
	/// </summary>
	/// <param name="forward">デフォルトで進みたい方向</param>
	/// <returns></returns>
	VECTOR3 CalcMoveVec(VECTOR3 forward);

	bool ThrouthCheckStoM(Object3D* obj, SphereCollider coll, VECTOR3* push, VECTOR3 speed, int per);
	void LoadMesh(std::string meshName);
	void LoadColMesh(std::string meshName);
	SphereCollider Collider() override;

	//移動ベクトルのセッター・ゲッター
	void SetVec(VECTOR3 vec) { speed = vec; }
	VECTOR3 GetVec() { return speed; }


	//吹っ飛び率のセッターゲッター
	void AddKBR(float KBR) { KnockBackRate += KBR; }//吹っ飛び率加算
	float GetKBR() { return KnockBackRate; }

	/// <summary>
	/// ヒット時の吹っ飛び処理
	/// </summary>
	/// <param name="atacker">攻撃側</param>
	/// <param name="difender">攻撃を受ける側</param>
	void KnockBack(Player* atacker, Player* difender);



	static int menNum;//プレイヤーの人数

	int GetDangerTime() { return dangerTime; }

	int plNo;//プレイヤー番号

	enum State {
		sOnGround = 0,
		sJump,
		sStop,
	};

private:

	void Input();

	float speedY; // Yの速度
	VECTOR3 speed;//移動速度
	float Timer;
	float boundTime;
	int airJump;

	//Animator* animator; // 部品のインスタンスをポインター型で準備
	enum AnimID {
		aIdle = 0,
		aRun = 1,
		aAttack1,
		aAttack2,
		aAttack3,

	};

	//１P２Pで操作の入力を変えるための変数
	DWORD inputForward;
	DWORD inputBack;
	DWORD inputRight;
	DWORD inputLeft;
	DWORD inputJump;
	DWORD inputLeanR;
	DWORD inputLeanL;


	int number;
	
	State state;
	void UpdateOnGround();
	void UpdateJump();

	float defKBR;//初期吹っ飛び率
	float KnockBackRate;//ふっとび率

	CFbxMesh* colMesh;
	//危険地帯にいる時間
	int dangerTime;

	int waitTime;//Stop()の待ち時間
	int wait;
	int changeState;
	int frame; // アニメーションのフレームを数える

	



};

