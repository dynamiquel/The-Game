#include "Order.cpp"

#pragma once
class PlayPile
{
	public:
		short topCard;
		Order order;
		PlayPile();
		PlayPile(const Order& order);
		void Reset();
		bool CanDeposit(const short& card) const;
		bool Deposit(const short& card);
};

