#include <iostream>
#include"AFN.h"
#include<stack>
int main()
{

	AFN automat;
	automat.readFromFile();
	automat.writeInCons();
	std::cout << std::endl;
	std::string choise, word;
	
	if (automat.verificaAutomatul() == true)
	{
		std::cout << "AUTOMATUL ESTE INTRODUS CORECT!" << std::endl;
		do {
			std::cout << "Word=";
			std::cin >> word;
			if (automat.backTr(word) == -1)
				std::cout << word << "-->BLOCAJ";
			else if (automat.backTr(word) == 1)
				std::cout << word << "-->ACCEPTAT";
			else if (automat.backTr(word) == 0)
				std::cout << word << "-->NEACCEPTAT";
			std::cout << std::endl << "Introduceti DA daca mai doriti sa continuati=";
			std::cin >> choise;
		} while (choise == "da");
	}
	else
	{
		std::cout << "Automatul nu este corect!";
	}
}