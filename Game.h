#include "Player.h"
#include "CardHandler.h"
#include "PlayerHandler.h"
#include <vector>

#pragma once
class Game
{
	public:
		Game();

	private:	
		CardHandler cardHandler;
		PlayerHandler playerHandler;

		bool running;

		void OnStart();
		void OnLoop();
		void OnPlayerWin(Player& activePlayer);
		void OnWin();
		void OnLoss();
		void OnEnd();
		void OnRestart();

		void PlayTurn(Player& activePlayer);
		short& ChooseCard(Player& activePlayer);
		short& ChoosePile();
		bool CheckForTurnEnd(Player& activePlayer, const short& cardsPlayed, const bool& forceEnd);

		void Test();
};