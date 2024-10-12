#pragma once
#include "GameObject.h"

class PlayerManager : public GameObject
{
public:

	PlayerManager(int num);//ƒvƒŒƒCƒ„[”‚ğˆø”‚É‚·‚é
	~PlayerManager();

	void ReduceSurvivor( int plNo );

private:
	std::vector<int> survivor;

};