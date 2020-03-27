#include "Player.h"

#pragma once
class RealPlayer : public Player
{
	public:
		RealPlayer();
		short& ChooseCard() override;
		short& ChoosePile() override;
};