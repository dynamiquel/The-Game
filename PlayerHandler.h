#include "Player.h"
#include "PlayPile.h"
#include <vector>

#pragma once
class PlayerHandler
{
	public:
		PlayerHandler();

		short GetPlayersSize() const;
		short& GetCurrentPlayer();
		void SetCurrentPlayer(const short& playerIndex);
		std::vector<Player>& GetPlayers();
		short& GetTotalNumberOfPlayerCards();

		void SetupPlayers();

		short& GetNextPlayer();
		void SetNextPlayer();
		bool CanPlay(const std::vector<short>& hand, const short& drawPileSize, const PlayPile* playPiles) const;
	
	private:
		const short MAX_PLAYERS = 5;
		std::vector<Player> players;
		short currentPlayer;

		short& SetupRealPlayers();
		short& SetupAIPlayers(const short& numOfPlayers);
};