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

		//Player();
		void AddCard(const short& card);
		void RemoveCard(const short& index);
		short GetHandSize() const;

		std::string HandToString();
		virtual short& ChooseCard() = 0;
		virtual short& ChoosePile() = 0;
};