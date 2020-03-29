// TheGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"
#include <iostream>

int main()
{
    std::cout << "Welcome to a C++ implementation of 'The Game' by Liam HALL.\n";

    std::cout 
        << "\nGuide\n"
        << "============================================================\n"
        << "\n 1-5 Players\n" 
        << "\n 1) Each player starts with 6-8 cards in their hand;\n"
        << "\n 2) There are four play piles."
        << "\n    The first two play piles start at 1 and only cards greater than the top card can be placed."
        << "\n    The other two play piles start at 100 and only card smaller than the top cards can be placed;\n"
        << "\n 3) The goal is to discard all 98 cards into the four piles;\n"
        << "\n 4) In any play pile, you can place a card that has a difference of exactly 10 from the top card;\n"
        << "\n 5) The player must play two cards each turn, or one card if the draw pile is empty;\n"
        << "\n 6) When a player finishes their turn, they refill their hand from the draw pile;\n"
        << "\n 7) Players are not allowed to reveal the numbers in their hands."
        << "\n    However, they are allowed to tell others not to play on certain play piles amongst other suggestions;\n"
        << "\n 8) If one player is unable to play the required number of cards. It's game over for everyone;\n"
        << "\n 9) The lower the score, the better.\n"
        << "\n============================================================\n";

    Game* game = new Game;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
