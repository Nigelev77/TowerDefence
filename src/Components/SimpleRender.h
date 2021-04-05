#pragma once

struct SimpleRenderComponent
{
	unsigned int id, vertexCount;
	SimpleRenderComponent(unsigned int id, unsigned int vertexCount)
		: id{id}, vertexCount{vertexCount}
	{}

	SimpleRenderComponent()
		: id{}, vertexCount{}
	{}
};