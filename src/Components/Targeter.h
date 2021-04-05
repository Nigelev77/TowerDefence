#pragma once
#include "../SingleIncludes/ecs.h"

struct TargeterComponent
{
	//Need to create some sort of target preference such as closest or enemy with largest amount of hp
	//But then would also need to debate on whether i want to keep a target member 
	//since it would be more likely that the target will change more frequently
	entt::entity target; //Current target to attack
	int shootFn; //Debating whether to use array of func ptr or just have func ptr here

	TargeterComponent(entt::entity target, int fn)
		: target{target}, shootFn(fn)
	{}

	TargeterComponent(int fn)
		: target{entt::null}, shootFn{fn}
	{}

	TargeterComponent()
		: target{entt::null}, shootFn{-1}
	{}
};