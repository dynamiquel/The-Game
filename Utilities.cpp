#include "Utilities.h"
#include <iostream>

short& Utilities::GetNumberInput()
{
	short x;
	std::cin >> x;

	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid number. Enter an integer: ";
		std::cin >> x;
	}

	return x;
}