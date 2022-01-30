#include <iostream>
#include"AFD.h"
#include<fstream>
int main()
{
	AFD afd;
	afd.readFromFile();
	afd.writeInCons();
	std::cout << "\n\n";

	afd.deleteInacTrans();
	afd.writeInCons();
	std::cout << "\n\n";


	afd.createMatrix();
	afd.writeInCons();
	afd.writeInFile();
	afd.writeInCons();

	
}

  