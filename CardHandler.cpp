#include "CardHandler.h"
#include <random>
#include <chrono>
#include <iostream>

CardHandler::CardHandler()
{
	playPiles[0] = PlayPile(Ascending);
	playPiles[1] = PlayPile(Ascending);
	playPiles[2] = PlayPile(Decending);
	playPiles[3] = PlayPile(Decending);
}

short CardHandler::GetDrawPileSize() const
{
	// Converts from size_t type to short.
	return static_cast<short>(drawPile.size());
}

// Returns the hand size based on the player count.
short CardHandler::GetHandSize(const size_t& playerCount)
{
	switch (playerCount)
	{
		// 1 player
		case 1:
			return 8;
			break;
		// 2 player
		case 2:
			return 7;
			break;
		default:
			return 6;
			break;
	}
}

// Gets the play pile of the given index. 
// If it's an invalid index, returns the first play pile.
PlayPile& CardHandler::GetPlayPile(const short& index)
{
	if (index < sizeof(playPiles) / sizeof(*playPiles))
		return playPiles[index];

	return playPiles[0];
}

PlayPile* CardHandler::GetPlayPiles()
{
	// TODO: insert return statement here
	return playPiles;
}

void CardHandler::SetupDrawPile()
{
	drawPile.clear();

	// Initialises the draw pile with 98 cards, from 2 to 99.
	for (short i = 2; i < 100; i++)
		drawPile.push_back(i);
}


void CardHandler::ShuffleDrawPile()
{
	// Creates a random seed based off the current time.
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	// Shuffles the draw pile based off the given seed.
	shuffle(drawPile.begin(), drawPile.end(), std::default_random_engine(seed));
}

// Resets all the play piles to default values.
void CardHandler::EmptyPlayPiles()
{
	for (PlayPile& playPile : playPiles)
	{
		playPile.Reset();
	}
}

// Gives the players cards for their hand.
void CardHandler::DealCards(std::vector<std::unique_ptr<Player>>& players)
{
	short handSize = GetHandSize(players.size());

	if (players.size() <= 0)
		return;

	// For every player, give them the required number of cards.
	for (auto& player : players)
	{
		while (player->GetHandSize() < handSize)
		{
			short card;
			if (WithdrawFromDrawPile(card))
				player->AddCard(card);
			else
			{
				break;
			}
		}
	}
}

bool CardHandler::WithdrawFromDrawPile(short& card)
{
	if (drawPile.size() > 0)
	{
		// Gets the card from the top of the draw pile.
		card = drawPile[drawPile.size() - 1];
		// Removes the card on the top of the draw pile.
		drawPile.erase(drawPile.end() - 1);
		return true;
	}

	return false;
}

void CardHandler::RefillHand(Player& player, const short& playerCount)
{
	printf("Player hand size: %d", player.GetHandSize());
	printf("Player count: %d", playerCount);
	printf("Max hand size: %d", GetHandSize(playerCount));
	while (player.GetHandSize() < GetHandSize(playerCount))
	{
		short cardToAdd;

		// If we were able to withdraw a card from the draw pile (not empty), then...
		if (WithdrawFromDrawPile(cardToAdd))
			player.AddCard(cardToAdd);
		else
		{
			// No more cards in draw pile.
			break;
		}
	}
}

std::string CardHandler::PlayPilesToString()
{
	std::string s = "Play Piles:";

	for (short i = 0; i < 2; i++)
		s.append("\n    (" + std::to_string(i + 1) + ") ^ - Top Card: " + std::to_string(playPiles[i].topCard));

	for (short i = 2; i < 4; i++)
		s.append("\n    (" + std::to_string(i + 1) + ") v - Top Card: " + std::to_string(playPiles[i].topCard));

	return s;
}
