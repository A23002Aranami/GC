#include "PlayScene.h"
#include "Player.h"
#include "Ground.h"
#include "Door.h"
#include "Dancer.h"
#include"camera.h"
#include"CsvReader.h"
#include<assert.h>
#include "Score.h"
#include "DrawScore.h"
#include "MochiTest.h"
#include "Map.h"
#include "PlayerManager.h"
#include "Skybox.h"
PlayScene::PlayScene()
{
	CsvReader* csv = new CsvReader("Data/config.csv");

	assert(csv->GetLines() > 0);//値が入っていない場合エラーにするための処理

	players = 0;//プレイヤーの人数を０で初期化

	for (int i = 1; i < csv->GetLines(); i++)//物体など題名の列を飛ばすためにiを1から始めている
	{
		std::string str = csv->GetString(i, 0);

		if (str.substr(0, 2) == "//") {}//先頭２文字が//だったら飛ばす
		else {
			Object3D* obj = nullptr;//すべてObject3Dを継承しているので、objで統一できる

			if (str == "PLAYER") {//Playerの数値入力

				players++;
				//プレイヤー固有変数を設定するためにポインタ取得
				Player* p = Instantiate<Player>();

				//キーバインドの設定
				p->SetKeyBind(csv->GetKeyDef(i, 4), csv->GetKeyDef(i, 5), csv->GetKeyDef(i, 6), csv->GetKeyDef(i, 7), csv->GetKeyDef(i, 8), csv->GetKeyDef(i, 9), csv->GetKeyDef(i, 10));
				//p->LoadMesh(csv->GetString(i,11));

				p->SetRotation(0, csv->GetFloat(i, 11) * DegToRad, 0);

				p->LoadColMesh(csv->GetString(i, 12));
				//プレイヤーの番号を割り振り
				p->SetPlNo(players);
				obj = p;
			}
			else if (str == "GROUND") {//GROUNDの数値入力
				obj = Instantiate<Ground>();
			}
			else if (str == "SKYBOX")
			{
				SkyBox* sky = Instantiate<SkyBox>();
				sky->LoadMesh(csv->GetString(i,4));

				obj = sky;
			}
			else//文字列ミスの時
			{
				assert(false);//強制終了
			}
			float x = csv->GetFloat(i, 1);
			float y = csv->GetFloat(i, 2);
			float z = csv->GetFloat(i, 3);

			obj->SetPosition(x, y, z);
			obj->SetCsvLine(i);

			Instantiate<Camera>();
			Score* sc = ObjectManager::FindGameObject<Score>();
			if (sc == nullptr) {//オブジェクトがまだ作られていなかったら作る
				sc = Instantiate<Score>();
				sc->DontDestroyMe();//シーン切替しても、オブジェクトを消されないようにする
			}
			sc->Clear();

			Instantiate<ScoreDraw>();

			//Instantiate<Ground>();


		}
	}

	Instantiate<Map>();
	new PlayerManager(players);//プレイヤーマネージャー実体化
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	//
	////Playerが残り一人になったらゲーム終了
	//std::list< Player* > pls = ObjectManager::FindGameObjects<Player>();
	//if (pls.size() <= 1) {
	//	Score* sc = ObjectManager::FindGameObject<Score>();
	//	Player* pl = ObjectManager::FindGameObject<Player>();
	//	sc->SetWinner( pl->plNo);
	//	SceneManager::ChangeScene("ResultScene");
	//}
}

void PlayScene::Draw()
{
}


