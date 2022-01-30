#include <iostream>
#include<fstream>
#include"FunctiiAnalizator.h"
int main()
{
	std::ifstream fin("data.in");
	FunctiiAnalizator t; 
	t.AnalizatorLexical(fin);
	t.afiseazaVector();
	t.afiseazaHashTabel();


}


