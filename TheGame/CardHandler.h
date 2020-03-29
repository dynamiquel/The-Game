#include "PlayPile.h"
#include "Player.h"
#include <vector>
#include <memory>

#pragma once
class CardHandler
{
	public:
		CardHandler();

		short GetDrawPileSize() const;
		short GetHandSize(const size_t& playerCount);
		PlayPile& GetPlayPile(const short& index);
		PlayPile* GetPlayPiles();

		void SetupDrawPile();
		void ShuffleDrawPile();
		void EmptyPlayPiles();
		void DealCards(std::vector<std::unique_ptr<Player>>& players);
		bool WithdrawFromDrawPile(short& card);
		void RefillHand(Player& player, const short& playerCount);

		std::string PlayPilesToString();

	private:
		std::vector<short> drawPile;
		PlayPile playPiles[4];
};

