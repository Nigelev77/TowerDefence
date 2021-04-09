#pragma once

struct CooldownComponent
{
	float cd; //Every iteration will be reduced
	CooldownComponent()
		: cd{0.0f}
	{}
	CooldownComponent(float time)
		: cd{time}
	{}
};