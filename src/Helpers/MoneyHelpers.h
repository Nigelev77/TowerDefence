#pragma once

#include "../SingleIncludes/ecs.h"



namespace Money
{
	void TransferToPlayer(Registry& registry, entt::entity sender);
	bool AttemptWithdraw(Registry& registry, int amount);
	void InitMoney(Registry& regsitry);
}