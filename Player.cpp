#include "Player.h"

Player::Player(const bool& isAI)
{
	this->isAI = isAI;
	completed = false;
}

// Adds the card to the player's hand.
void Player::AddCard(const short& card)
{
	hand.push_back(card);
}

// Removes the card at the index index from the player's hand.
void Player::RemoveCard(const short& index)
{
	if (hand.size() > index)
		hand.erase(hand.begin() + index);
}

// Returns the size of the player's hand.
short Player::GetHandSize() const
{
	// Converts from size_t type to short.
	return static_cast<short>(hand.size());
}

// Represents the player's hand in a formatted string.
std::string Player::HandToString()
{
	std::string s = "Your hand includes:";

	// Adds all the cards in the hand (with its index) to the readable string.
	for (int i = 0; i < hand.size(); i++)
		s.append("\n    (" + std::to_string(i + 1) + ") " +  std::to_string(hand[i]));

	return s;
}