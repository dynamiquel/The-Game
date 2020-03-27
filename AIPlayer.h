#include "Player.h"


#pragma once
class AIPlayer : public Player
{
	public:
		AIPlayer();
		short& ChooseCard() override;
		short& ChoosePile() override;
};

