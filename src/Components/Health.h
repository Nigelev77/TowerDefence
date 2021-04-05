#pragma once

struct HealthComponent
{
	float health;
	float maxHealth;

	HealthComponent(float max, float current)
		: health{ current }, maxHealth{ max }
	{}

	HealthComponent(float max)
		: health{ max }, maxHealth{ max }
	{}

	HealthComponent()
		: health{ 0.0f }, maxHealth{ 0.0f }
	{}
};