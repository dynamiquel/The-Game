#include "Player.h"


#pragma once
class AIPlayer : public Player
{
	public:
		AIPlayer();
		short& ChooseCard(const PlayPile* playPiles = nullptr) override;
		short& ChoosePile() override;
};

