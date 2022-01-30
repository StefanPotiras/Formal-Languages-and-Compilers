#include <iostream>
#include<fstream>
#include <string>
#include"Productie.h"
#include"Gramatica.h"
#include<unordered_set>
void afisareCuvinte(std::unordered_set<std::string>cuvantUnic)
{
	int i = 1;
	for (auto index:cuvantUnic)
	{
		std::cout <<i<<"->"<< index<<"\n";
		
		i++;
	}
}
void meniu(Gramatica gram)
{
	std::unordered_set<std::string>cuvantUnic;
	bool meniu = true;
	int alegere; int n;
	std::string cuvant;
	while (meniu)
	{
		std::cout << "\n";
		std::cout << "Apasa 1 pentru a introduce numarul de cuvinte generate!" << "\n";
		std::cout << "Apasa 2 pentru a verifica gramatica!" << "\n";
		std::cout << "Apasa 3 pentru generarea simpla!" << "\n";
		std::cout << "Apasa 4 pentru generarea complexa!" << "\n";
		std::cout << "Apasa 5 pentru a afisa gramatica!"<<"\n";
		std::cout << "Apasa 6 pentru a iesi!" << "\n";
		std::cin >> alegere;
		switch (alegere)
		{
		case 1:
		{
			std::cout << "n=";
			std::cin >> n;
		}
		break;
		case 2:
		{
			gram.verificare();
		}
		break;
		case 3:
		{
			gram.generateNWords(0,n);
		}
		break;
		case 4:
		{
			gram.generateNWords(1, n);
		}
		break;
		case 5:
		{
			std::cout<<gram;
		}
		break;
		case 6:
		{
			meniu = false;
		}
		break;
		}
	}
}
int main()
{
	std::ifstream fin("date.in");
	Gramatica gram;
	fin >> gram;
	std::cout << gram << "\n";
	meniu(gram);	
}



