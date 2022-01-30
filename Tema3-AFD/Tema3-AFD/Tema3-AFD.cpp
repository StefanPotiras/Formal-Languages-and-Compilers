#include <iostream>
#include"AFD.h"
#include<map>
int main()
{
	/*AFD automat;
	automat.readFromFile();
	automat.writeInCons();
	std::cout << std::endl;
	std::string choise,word;
	if (automat.verificaAutomatul() == true)
	{
		std::cout << "AUTOMATUL ESTE INTRODUS CORECT!" << std::endl;
		do {
			std::cout << "Word=";
			std::cin >> word;
			if (automat.verificaCuvantul(word) == -1)
				std::cout << word << "-->BLOCAJ";
			else if (automat.verificaCuvantul(word) == 1)
				std::cout << word << "-->ACCEPTAT";
			else if (automat.verificaCuvantul(word) == 0)
				std::cout << word << "-->NEACCEPTAT";
			std::cout << std::endl << "Introduceti DA daca mai doriti sa continuati=";
			std::cin >> choise;
		} while (choise == "da");
	}
	else
	{
		std::cout << "Automatul nu este corect!";
	}*/
	std::map<std::pair<std::string, std::string>, int>test;
	test[std::make_pair("tu", "eu")] = 2;
	test[std::make_pair("tu", "da")] = 22;
	test[std::make_pair("tu", "nu")] = 21;
	std::pair<std::string, std::string>pereche;
	pereche.first = "tu";
     pereche.second = "nu";
	auto findd = test.find(pereche);
	if (findd != test.end())
	{
		std::cout << "Da";
	}


}

