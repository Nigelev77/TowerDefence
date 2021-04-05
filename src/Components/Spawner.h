#pragma once
#include <vector>


struct SpawnerComponent
{
	const float* spawnTimes;
	const int* spawnNum;
	const int* spawnTypes;
	int currentEnemy; //Used to index the arrays
	int enemyCount; //Used as the total enemy slots in wave
	
	SpawnerComponent(const int* num, const int* types, const float* times, int count)
		: spawnTimes{times}, spawnNum{num}, currentEnemy{0}, enemyCount{count}, spawnTypes{types}
	{}

	SpawnerComponent()
		: spawnTimes{}, spawnNum{}, currentEnemy{0}, spawnTypes{}, enemyCount{0}
	{}


};