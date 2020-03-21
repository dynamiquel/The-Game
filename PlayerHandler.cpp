#include "PlayerHandler.h"
#include "Utilities.h"
#include <iostream>

PlayerHandler::PlayerHandler()
{
	currentPlayer = -1;
}

// Returns the size of the players' vector.
short PlayerHandler::GetPlayersSize() const
{
	return static_cast<short>(players.size());
}

// Returns the index of the current player.
short& PlayerHandler::GetCurrentPlayer()
{
	return currentPlayer;
}

void PlayerHandler::SetCurrentPlayer(const short& playerIndex)
{
	currentPlayer = playerIndex;
}

// Returns a reference of the players' vector.
std::vector<Player>& PlayerHandler::GetPlayers()
{
	return players;
}

short& PlayerHandler::GetTotalNumberOfPlayerCards()
{
	short totalCount = 0;

	for (Player& player : players)
		totalCount += player.GetHandSize();

	return totalCount;
}

// Requests the number of players to play and adds them to the players' vector.
void PlayerHandler::SetupPlayers()
{
	// Gets the number of real and AI players.
	short numOfPlayers = SetupRealPlayers();
	short numOfAI = SetupAIPlayers(numOfPlayers);

	// Clears the players vector in case this was a restart and it already had players in it.
	players.clear();

	short i = 0;
	// Adds the real players to the player's vector.
	while (i < numOfPlayers)
	{
		players.push_back(Player(false));
		i++;
	}

	i = 0;
	// Adds the AI players to the player's vector.
	while (i < numOfAI)
	{
		players.push_back(Player(true));
		i++;
	}
}

// Requests and returns the number of real players.
short& PlayerHandler::SetupRealPlayers()
{
	// Ask for the number of real players.
	while (true)
	{
		std::cout << "\nEnter the number of real players: ";

		short& inputNumber = Utilities::GetNumberInput();

		if (inputNumber >= 1 && inputNumber <= MAX_PLAYERS)
		{
			return inputNumber;
			break;
		}

		std::cout << "Number out of range. Must be >= 1 and <= " << MAX_PLAYERS;
	}
}

// Requests and returns the number of AI players.
short& PlayerHandler::SetupAIPlayers(const short& numOfPlayers)
{
	// If there's room for AI players, ask for the number of AI players.
	if (numOfPlayers < MAX_PLAYERS)
	{
		while (true)
		{
			std::cout << "\nEnter the number of AI players: ";

			short& inputNumber = Utilities::GetNumberInput();

			if (numOfPlayers + inputNumber <= MAX_PLAYERS)
			{
				return inputNumber;
				break;
			}

			std::cout << "Number out of range. Must be >= 0 and <= " << MAX_PLAYERS - numOfPlayers;
		}
	}
}

// Returns the index of the player who should play next.
short& PlayerHandler::GetNextPlayer()
{
	short potentialNextPlayer = currentPlayer;

	// Loops through all the players until it finds one that hasn't
	// completed their run.
	// Potential infinite loop if the OnPlayerWin method doesn't work
	// as intended.
	uint8_t timesLooped = 0;
	while (true)
	{
		if (potentialNextPlayer + 1 >= players.size())
		{
			potentialNextPlayer = 0;
			//printf("\nRestarting from player 0, %d", potentialNextPlayer);
		}
		else
		{
			potentialNextPlayer++;
			//printf("\nUp we go!, %d", potentialNextPlayer);
		}

		if (!players[potentialNextPlayer].completed)
		{
			//printf("\nNext player: %d", potentialNextPlayer);
			return potentialNextPlayer;
		}

		//printf("\nCurrent player: %d  -  Potential player: %d", currentPlayer, potentialNextPlayer);
		// Checks for unusual behaviour.
		if (potentialNextPlayer == currentPlayer)
		{
			timesLooped++;

			if (timesLooped >= 2)
			{
				printf("\nSomething is wrong, this shouldn't be happening...");

				if (timesLooped >= 5)
				{
					printf("\nI don't feel so well... I'm going to break now.");
					break;
				}
			}
		}
	}
}

void PlayerHandler::SetNextPlayer()
{
	short& nextPlayerIndex = GetNextPlayer();
	currentPlayer = nextPlayerIndex;
	//printf("\nNew current player: %d", currentPlayer);
}

// Returns true if the player is able to play.
bool PlayerHandler::CanPlay(const std::vector<short>& hand, const short& drawPileSize, const PlayPile* playPiles) const
{
	short playableCards = 0;

	for (short card : hand)
	{
		// Checks all the play piles to check if the card can be played in them.
		for (short i = 0; i < 4; i++)
		{
			if (playPiles[i].CanDeposit(card))
			{
				playableCards++;
				break;
			}
		}

		// If the player has two playable cards, or has one playable card and the draw pile is empty, they can play.
		if (playableCards == 2 || (playableCards == 1 && drawPileSize == 0))
			return true;
	}

	return false;
}