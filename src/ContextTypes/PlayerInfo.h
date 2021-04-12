#pragma once

struct PlayerInfo
{
	int health, money, score;
	PlayerInfo(int health, int money, int score)
		: health{health}, money{money}, score{score}
	{}
	PlayerInfo()
		: health{0}, money{0}, score{0}
	{}
};