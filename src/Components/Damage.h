#pragma once

struct DamageComponent
{
	float dmg;
	DamageComponent()
		: dmg{0.0f}
	{}

	DamageComponent(float d)
		: dmg{d}
	{}
};