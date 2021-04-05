#pragma once


struct ScaleComponent
{
	float x, y, z;

	ScaleComponent()
		: x{0.0f}, y{0.0f}, z{0.0f}
	{}
	ScaleComponent(float x, float y, float z)
		: x{x}, y{y}, z{z}
	{}
	ScaleComponent(float a)
		: x{a}, y{a}, z{a}
	{}
};

