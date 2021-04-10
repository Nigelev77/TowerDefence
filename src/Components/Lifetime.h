#pragma once

struct LifetimeComponent
{
	float lifetime, maxLifetime;
	LifetimeComponent()
		: lifetime{0.0f}, maxLifetime{0.0f}
	{}
	LifetimeComponent(float time)
		: lifetime{time}, maxLifetime{time}
	{}
};