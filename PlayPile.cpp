#include "PlayPile.h"
#include <cmath>

PlayPile::PlayPile()
{
	order = Ascending;
	topCard = -1;
}

PlayPile::PlayPile(const Order& order)
{
	this->order = order;
	topCard = -1;
}

void PlayPile::Reset()
{
	if (order == Ascending)
		topCard = 1;
	else if (order == Decending)
		topCard = 100;
}

// Checks if the given card can be played in this pile.
bool PlayPile::CanDeposit(const short& card) const
{
	// If the difference between the cards are 10, return true.
	if (std::abs(topCard - card) == 10)
		return true;

	switch (order)
	{
		case Ascending:
			if (card > topCard)
				return true;
			break;
		case Decending:
			if (card < topCard)
				return true;
	}

	return false;
}

bool PlayPile::Deposit(const short& card)
{
	if (CanDeposit(card))
	{
		topCard = card;
		return true;
	}

	return false;
}