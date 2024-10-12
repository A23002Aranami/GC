#pragma once

#include "Object3D.h"
#include "GameObject.h"
#include "CsvReader.h"

//マップ生成クラス
class Map : public GameObject
{
public:
	Map();
	~Map();
	
	int GetMAPSIZE();
private:

	//マップの最大サイズ
	static const int MAP_MAXSIZE = 10;

};

//マップブロッククラス

class Block : public Object3D
{
public:
	Block();
	~Block();


	/// <summary>
	/// ブロックの情報を設定する関数
	/// </summary>
	/// <param name="x">ブロックのX座標</param>
	/// <param name="y">ブロックのY座標</param>
	/// <param name="z">ブロックのZ座標</param>
	/// <param name="type">ブロックの種類</param>
	void SetStatus(float x,float y, float z, int type);

	/// <summary>
	/// メッシュとメッシュコライダーを設定する
	/// </summary>
	/// <param name="filepass">ファイルのパス</param>
	void SetMesh(const TCHAR* filepass);
private:
	//ブロックの種類
	static const enum State
	{
		NoBlock,	//ブロック無し
		Blank ,		//単色のブロック
	};

	int bType;	//ブロックの種類
};
