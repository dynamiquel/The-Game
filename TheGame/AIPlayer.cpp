#include "AIPlayer.h"
#include "Utilities.h"
#include <iostream>

short selectedPile = -1;

AIPlayer::AIPlayer()
{
	isAI = true;
	completed = false;
}

// Asks the user to choose a card and returns its index.
short& AIPlayer::ChooseCard(const PlayPile* playPiles)
{
	std::cout << "\n\n  Choose the card you want to play (the number in the brackets) or enter \"0\" to end your turn: ";

	// The max difference the player's card and the play pile's card can have in order to play the card.
	// Start at 1 = highest chance of choosing best card.
	short maxDifference = 1;
	// Chooses a random card to start at.
	short startCardIndex = rand() % GetHandSize();

	short lowestDifference = SHRT_MAX;
	short lowestDifferencePileIndex = -1;

	while (true)
	{
		short currentCardIndex = startCardIndex;

		while (true)
		{
			// For every play pile...
			for (short i = 0; i < 4; i++)
			{
				// Calculates the difference between the current card and the top card of the current play pile.
				short currentDifference = std::abs(hand[currentCardIndex] - playPiles[i].topCard);
				
				// Debugging
				/*
				printf("\nCurrent card: %d", hand[currentCardIndex]);
				printf("\nCurrent card index: %d", currentCardIndex);
				printf("\nTop card: %d", playPiles[i].topCard);
				printf("\nCurrent difference: %d", currentDifference);
				printf("\nLowest difference: %d", lowestDifference);
				printf("\nMax difference: %d\n", maxDifference);
				*/

				// If the difference between the current card and play pile is <= the max difference,
				// check if the difference is the lowest one yet and can be played.
				// If so, update the lowest values to the current values.
				if (currentDifference <= maxDifference)
					if (currentDifference < lowestDifference && playPiles[i].CanDeposit(hand[currentCardIndex]))
					{
						lowestDifference = currentDifference;
						lowestDifferencePileIndex = i;
					}
			}

			// If the lowest difference is less than the max difference threshold, play the current card and store the
			// play pile index for later.
			if (lowestDifference <= maxDifference)
			{
				selectedPile = lowestDifferencePileIndex;
				return currentCardIndex;
			}

			// The current card can't be played in any play piles with the max difference threshold, 
			// so choose the next card.
			if (currentCardIndex++ >= GetHandSize() - 1)
				currentCardIndex = 0;


			// If we have looped back to start card, break the loop so we can increase the difference and try again.
			if (currentCardIndex == startCardIndex)
				break;
		}

		// Since no cards can be played with the given range, increase the max difference and check again.
		// 1 = will always choose the lowest card possible. Increase to make the AI 'dumber' and rely more on luck, and increase performance.
		maxDifference += 1;

		// Breaks the loop if for some reason the AI can't play their cards.
		// This should never happen as the CanPlay() method should give the AI a defeat before their turn.
		if (maxDifference > 98)
			break;
	}

	// Return -1 to end the turn.
	short endTurn = -1;
	return endTurn;
}

// Asks the user to choose a play pile and returns its index.
short& AIPlayer::ChoosePile()
{
	std::cout << "\n\n  Choose the play pile you want to put your card in (the number in the brackets) or enter \"0\" to end your turn: ";

	// Returns the pile index that was calculated when the AI chose their card.
	return selectedPile;
}