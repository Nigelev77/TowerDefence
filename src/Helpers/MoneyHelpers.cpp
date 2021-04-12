#include "MoneyHelpers.h"

#include "../Components/Reward.h"

#include "../ContextTypes/PlayerInfo.h"

static PlayerInfo* player{};

namespace Money
{

	void TransferToPlayer(Registry& registry, entt::entity sender)
	{
		player->money += registry.get<RewardComponent>(sender).reward;
	}

	bool AttemptWithdraw(Registry& registry, int amount)
	{
		if (!(player->money >= amount)) return false;
		player->money -= amount;
		return true;
	}

	void InitMoney(Registry& registry)
	{
		player = &registry.ctx<PlayerInfo>();
	}
}


