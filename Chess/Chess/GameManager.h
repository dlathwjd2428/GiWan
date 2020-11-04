#pragma once
#include"Player.h"

enum PLAYER
{
	PLAYER_1,
	PLAYER_2,
	PLAYER_MAX
};
//Turn % 2 != 0일 떄, 플레이어1의 차례
class GameManager
{
private:
	int m_iTurn;
	Player m_Players[PLAYER_MAX];
public:
	GameManager();
	~GameManager();
};

