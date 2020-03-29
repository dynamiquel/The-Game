#include "Player.h"

#pragma once
class RealPlayer : public Player
{
	public:
		RealPlayer();
		short& ChooseCard(const PlayPile* playPiles = nullptr) override;
		short& ChoosePile() override;
};