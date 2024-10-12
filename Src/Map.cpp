#include "Map.h"

Map::Map()
{
	CsvReader* csv = new CsvReader("Data/map01.csv");
	for (int i = 0; i < MAP_MAXSIZE; i++)
	{
		for (int j = 0; j < MAP_MAXSIZE; j++)
		{
			Block* block = Instantiate<Block>();
			 int type = csv->GetInt(i, j);
			block->SetStatus(i,0,j,type);
		}
	}
}

Map::~Map()
{
}

int Map::GetMAPSIZE()
{
	return MAP_MAXSIZE;
}


//以下ブロックの処理

Block::Block()
{
	//ブロックのタイプをブランクに初期化
	bType = Blank;
	//座標を0,0,0で初期化する
	transform.position = VECTOR3(0,0,0);

	//タグをセットする
	SetTag("STAGEOBJ");
}

Block::~Block()
{
	if (mesh != nullptr) {
		delete mesh;
		mesh = nullptr;
	}
}

void Block::SetStatus(float x, float y, float z, int type)
{
	SetPosition(x,y,z);
	bType = type;
	
	switch (type)//指定されたブロックの種類のメッシュをロード
	{
	case NoBlock:
		DestroyMe();
		break;
	case Blank:
		SetMesh("Data/Map/wallStone01.mesh");
		break;
	default:
		break;
	}

	
}

void Block::SetMesh(const TCHAR* filepass)
{
	mesh = new CFbxMesh();
	mesh->Load(filepass);
	meshCol = new MeshCollider;
	meshCol->MakeFromMesh(mesh);
}
