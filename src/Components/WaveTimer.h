#pragma once

struct WaveTimerComponent
{
	float waveTime; //Current time on interval
	float spawnInterval; //interval
	int enemyCount; //Number of enemies spawned on the current wave enemy index

	WaveTimerComponent(float interval)
		: spawnInterval{interval}, waveTime{0.0f}, enemyCount{0}
	{}

	WaveTimerComponent()
		: spawnInterval{0}, waveTime{0.0f}, enemyCount{0}
	{}

};