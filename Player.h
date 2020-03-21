#include<vector>
#include<cstring>
#include<string>

#pragma once
class Player
{
	public:
		char name[16];
		std::vector<short> hand;
		bool isAI;
		bool completed;

		Player(const bool& isAI);
		void AddCard(const short& card);
		void RemoveCard(const short& index);
		short GetHandSize() const;

		std::string HandToString();
};

