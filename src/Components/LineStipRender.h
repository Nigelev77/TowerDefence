#pragma once

struct LineStripRenderComponent
{
	unsigned int id, vertexCount;
	LineStripRenderComponent(unsigned int id, unsigned int vertexCount)
		: id{ id }, vertexCount{ vertexCount }
	{}

	LineStripRenderComponent()
		: id{}, vertexCount{}
	{}
};
