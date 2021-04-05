#pragma once


struct PathComponent
{
	int boxesPast; //How many boxes it has taken
	int nextIndex; //The next index of the boxes

	PathComponent(int boxes, int index)
		: boxesPast{boxes}, nextIndex{index}
	{}

	PathComponent()
		: boxesPast{0}, nextIndex{1}
	{}

};