#include "Player.h"
#include "PlayPile.h"
#include <vector>
#include <memory>

#pragma once
class PlayerHandler
{
	public:
		PlayerHandler();

		short GetPlayersSize() const;
		short& GetCurrentPlayer();
		void SetCurrentPlayer(const short& playerIndex);
		std::vector<std::unique_ptr<Player>>& GetPlayers();
		short& GetTotalNumberOfPlayerCards();

		void SetupPlayers();

		short& GetNextPlayer();
		void SetNextPlayer();
		bool CanPlay(const std::vector<short>& hand, const short& drawPileSize, const PlayPile* playPiles, const short& cardsPlayed) const;
	
	private:
		const short MAX_PLAYERS = 5;
		// A way to create a vector of an abstract class. (It took me about two hours to find a way to do this)
		std::vector<std::unique_ptr<Player>> players;
		short currentPlayer;

		short& SetupRealPlayers();
		short& SetupAIPlayers(const short& numOfPlayers);
};