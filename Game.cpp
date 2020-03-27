#include "Game.h"
#include "Utilities.h"
#include <string>
#include <iostream>
#include <fstream>
#include <memory>

// TODO:
// Add AI players

Game::Game()
{
	running = false;

	//printf("\nGame created!");
	//Test();

	OnStart();
}

// Called after construction.
void Game::OnStart()
{
	//printf("\n0/6 Adding cards to draw pile...");
	cardHandler.SetupDrawPile();
	//printf("\n1/6 Cards added to draw pile.");
	//printf("\n1/6 Shuffling draw pile...");
	cardHandler.ShuffleDrawPile();
	//printf("\n2/6 Shuffled draw piles.");
	//printf("\n2/6 Emptying play piles...");
	cardHandler.EmptyPlayPiles();
	//printf("\n3/6 Emptied play piles.");
	//printf("\n3/6 Setting up players...");
	playerHandler.SetupPlayers();
	//printf("\n4/6 Players set up.");
	//printf("\n4/6 Dealing cards...");
	cardHandler.DealCards(playerHandler.GetPlayers());
	//printf("\n5/6 Cards dealt.");
	//printf("\n5/6 Setting first player...");
	playerHandler.GetCurrentPlayer() = 0;
	//printf("\n6/6 First player set.");

	running = true;

	while (running)
		OnLoop();
}

// Game's main loop. Starts after OnStart(). Loops while 'running' is true.
void Game::OnLoop()
{
	printf("\n\n============================================================");
	printf("\n\nCurrent Player: %d", playerHandler.GetCurrentPlayer());

	// Gets the unique pointer of the player currently playing.
	// Converts the unique pointer to a reference to remove the 'it is a deleted function' error.
	Player& activePlayer = *(playerHandler.GetPlayers()[playerHandler.GetCurrentPlayer()]);

	PlayTurn(activePlayer);

	// If the game is still running by the time we reached the end of the loop, set the next player.
	if (running)
		playerHandler.SetNextPlayer();
}

// Called whenever a player completes their run (empties their hand).
void Game::OnPlayerWin(Player& activePlayer)
{
	printf("\n\n  ==========================================================");
	printf("\n\n  Player '%s' has completed their run.", activePlayer.name);
	printf("\n\n  ==========================================================");

	activePlayer.completed = true;

	bool allPlayersCompleted = true;

	// If any player has not completed their turn, set allPlayersCompleted
	// to false.
	for (auto& player : playerHandler.GetPlayers())
	{
		if (!player->completed)
		{
			allPlayersCompleted = false;
			break;
		}
	}

	// If all players have completed their runs, check if they have won or lost.
	if (allPlayersCompleted)
	{
		// No cards left in draw pile = win; else, loss.
		if (cardHandler.GetDrawPileSize() == 0)
			OnWin();
		else
			OnLoss();
	}
}

// Called when the game is won.
void Game::OnWin()
{
	running = false;

	printf("\n\n============================================================");
	printf("\n\nThe game has been beaten. Well played!");
	printf("\n\n============================================================");

	// Do win stuff.

	OnEnd();
}

// Called when the game is lost.
void Game::OnLoss()
{
	running = false;

	// Calculate player score (player hand count + draw pile)
	short totalScore = 0;
	totalScore += (playerHandler.GetTotalNumberOfPlayerCards() + cardHandler.GetDrawPileSize());

	printf("\n\n============================================================");
	printf("\n\nMission failed, we'll get 'em next time.");
	printf("\nTotal score: %d", totalScore);
	printf("\n\n============================================================");

	OnEnd();
}

// Called when the game has ended (after OnWin() and OnLoss()).
void Game::OnEnd()
{
	// Say thanks for playing and Liam Hall credit.
	// Ask the player if they want another game or quit the game.
	printf("\n\nThanks for playing my implementation of 'The Game'.");
	printf("\nEnter \"yes\" if you wish to play another round: ");

	// If the user entered yes, restart the game
	std::string s;
	std::cin >> s;

	if (s == "yes" || s == "y" || s == "Yes")
	{
		OnRestart();
		return;
	}

	printf("\n\nExiting application...");
	exit(1);
}

// Called when the game is restarted.
void Game::OnRestart()
{
	OnStart();
}

void Game::PlayTurn(Player& activePlayer)
{
	// Keeps track of the number of cards the player has played.
	short cardsPlayed = 0;

	LOOP:while (true)
	{
		std::cout << "\n\n  " << "Cards left in draw pile: " << cardHandler.GetDrawPileSize();

		// Prints out the player's hand.
		std::cout << "\n\n  " << activePlayer.HandToString();

		// Prints out the top cards of each play pile.
		std::cout << "\n\n  " << cardHandler.PlayPilesToString();

		if (!playerHandler.CanPlay(activePlayer.hand, cardHandler.GetDrawPileSize(), cardHandler.GetPlayPiles(), cardsPlayed))
		{
			printf("\n\n  You cannot play the required number of cards to complete your turn.");
			OnLoss();
			return;
		}

		// Asks the user to choose a card and stores its index.
		short cardIndex = activePlayer.ChooseCard();

		// If user entered 0, then end the player's turn.
		if (cardIndex == -1)
		{
			if (CheckForTurnEnd(activePlayer, cardsPlayed, true))
				return;

			printf("\n  ==========================================================");
			goto LOOP;
		}

		short& card = activePlayer.hand[cardIndex];

		printf("\n  You selected card: %d (%d)", cardIndex + 1, card);

		// Asks the user to choose a pile and stores its index.
		short pileIndex = activePlayer.ChoosePile();

		// If user entered 0, then end the player's turn.
		if (pileIndex == -1)
		{
			if (CheckForTurnEnd(activePlayer, cardsPlayed, true))
				return;

			printf("\n  ==========================================================");
			goto LOOP;
		}

		printf("\n  You selected pile: %d", pileIndex + 1);

		// Gets the selected play pile.
		PlayPile& selectedPile = cardHandler.GetPlayPile(pileIndex);

		// If the selected card can be deposited in the selected pile,
		// then add the card to the pile and remove it from the player's hand.
		if (selectedPile.Deposit(card))
		{
			printf("\n  Card played (%d in play pile %d)", card, pileIndex + 1);
			activePlayer.RemoveCard(cardIndex);
			cardsPlayed++;
		}
		else
			printf("\n  Your card (%d) cannot be added into this pile.", card);


		if (CheckForTurnEnd(activePlayer, cardsPlayed, false))
			return;

		printf("\n\n  ==========================================================");	
	}
}

// Returns true if the player's turn has ended, false otherwise.
bool Game::CheckForTurnEnd(Player& activePlayer, const short& cardsPlayed, const bool& forceEnd)
{
	// If the user has passed their turn, check if they have won or ask if they want to continue.
	if (cardsPlayed >= 2 || (cardsPlayed == 1 && cardHandler.GetDrawPileSize() == 0))
	{
		// If the player won.
		if (activePlayer.GetHandSize() == 0)
		{
			OnPlayerWin(activePlayer);
			return true;
		}

		printf("\n\n  You have played the minimum number of required cards. Do you wish to keep going? ");

		// If the user entered no, end their turn.
		std::string s;
		std::cin >> s;

		if (s == "no" || s == "n" || s == "No")
		{
			// Refill cards to max.
			//cardHandler.RefillHand(activePlayer, playerHandler.GetPlayersSize());
			return true;
		}
	}
	// If the player force ended their turn and they didn't have the minimum number of cards to pass, 
	// ask them to confirm their choice before ending the game as a loss.
	else if (forceEnd)
	{
		printf("\n\n  Enter \"yes\" to confirm your choice to forfeit the game: ");

		// If the user entered yes, end their turn.
		std::string s;
		std::cin >> s;

		if (s == "yes" || s == "y" || s == "Yes")
		{
			// End the game as a loss.
			OnLoss();
			return true;
		}
	}

	return false;
}

// Debugging purposes.
void Game::Test()
{
	printf("\n\n============================================================");
	printf("\n\nTesting:\n");
	printf("\nDraw Pile Size: - Expected: 98 - Result: %d", cardHandler.GetDrawPileSize());
	printf("\nGetHandSize() - Expected: 6 - Result: %d", cardHandler.GetHandSize(playerHandler.GetPlayersSize()));
	printf("\nPlayerPile().order - Expected: 1 - Result: %d", cardHandler.GetPlayPile(3).order);
	printf("\nPlayerPile().topCard - Expected: -1 - Result: %d", cardHandler.GetPlayPile(1).topCard);

	cardHandler.EmptyPlayPiles();
	printf("\nPlayerPile 1 Reset - Expected: 1 - Result: %d", cardHandler.GetPlayPile(0).topCard);
	printf("\nPlayerPile 4 Reset - Expected: 100 - Result: %d", cardHandler.GetPlayPile(3).topCard);

	short withdrawnCard;
	if (cardHandler.WithdrawFromDrawPile(withdrawnCard))
	{
		printf("\nWithdrawn Card - Expected: 99 - Result %d", withdrawnCard);
	}

	printf("\n\n============================================================\n");
}