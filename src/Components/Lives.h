#pragma once


struct LivesComponent
{
	int lifeCount;

	LivesComponent(int lives)
		: lifeCount{lives}
	{}

	LivesComponent()
		: lifeCount{0}
	{}
};