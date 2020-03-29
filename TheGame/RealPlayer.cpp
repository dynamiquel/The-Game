#include "Player.h"
#include "Utilities.h"
#include "RealPlayer.h"
#include <iostream>

RealPlayer::RealPlayer()
{
	isAI = false;
	completed = false;
}

// Asks the user to choose a card and returns its index.
short& RealPlayer::ChooseCard(const PlayPile* playPiles)
{
	while (true)
	{
		std::cout << "\n\n  Choose the card you want to play (the number in the brackets) or enter \"0\" to end your turn: ";
		short card = Utilities::GetNumberInput();

		if (card > -1 && card <= GetHandSize())
		{
			card--;
			return card;
		}

		std::cout << "  Number out of range. Must be > 0 and <= " << GetHandSize();
	}
}

// Asks the user to choose a play pile and returns its index.
short& RealPlayer::ChoosePile()
{
	while (true)
	{
		std::cout << "\n\n  Choose the play pile you want to put your card in (the number in the brackets) or enter \"0\" to end your turn: ";
		short& pile = Utilities::GetNumberInput();

		if (pile > -1 && pile <= 4)
		{
			pile--;
			return pile;
		}

		std::cout << "  Number out of range. Must be > 0 and <= 4";
	}
}