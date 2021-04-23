#pragma once

enum class State
{
	UP,
	PRESSED,
	HELD,
	RELEASED
};

struct Position
{
	double x, y;
};

struct InputStates
{
	State Ws, As, Ss, Ds, SPACEs, Qs; //The s represents state
	Position lastPos, currPos; //Last and current position of the mouse to get a dx and dy
	float xOff, yOff; //For scroll
	bool W, A, S, D, SPACE, Q;
	bool MouseFree;
	bool LButton, RButton;
};