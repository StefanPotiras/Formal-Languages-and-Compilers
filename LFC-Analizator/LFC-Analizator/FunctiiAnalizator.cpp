#include "FunctiiAnalizator.h"
#include<fstream>
#include<iostream>
#include<algorithm>
#include<unordered_map>
void FunctiiAnalizator::AnalizatorLexical(std::ifstream& fin)
{
	std::string word;

	while (fin >> word)
	{
		AnalizeazaLiteraCuLitera(word);
	}
}

bool FunctiiAnalizator::VerificaOperatoriNumerici(char litera)
{
	if (litera == '*')
	{
		vectorToken.emplace_back(std::make_pair("token_OPR", "*"));
		return true;
	}
	else if (litera == '/' && vectorToken[vectorToken.size() - 1].first == "token_ID")
	{
		vectorToken.emplace_back(std::make_pair("token_OPR", "/"));
		return true;
	}
	else if (litera == '/' && vectorToken[vectorToken.size() - 1].first == "token_NUM")
	{
		vectorToken.emplace_back(std::make_pair("token_OPR", "/"));
		return true;
	}
	else if (litera == '+' && vectorToken[vectorToken.size() - 1].first == "token_NUM")
	{
		vectorToken.emplace_back(std::make_pair("token_OPR", "+"));
		return true;
	}
	else if (litera == '+' && vectorToken[vectorToken.size() - 1].first == "token_ID")
	{
		vectorToken.emplace_back(std::make_pair("token_OPR", "+"));
		return true;
	}
	else if (litera == '-' && vectorToken[vectorToken.size() - 1].first == "token_NUM")
	{
		vectorToken.emplace_back(std::make_pair("token_OPR", "-"));
		return true;
	}
	else if (litera == '-' && vectorToken[vectorToken.size() - 1].first == "token_ID")
	{
		vectorToken.emplace_back(std::make_pair("token_OPR", "-"));
		return true;
	}
	return false;
}

bool FunctiiAnalizator::VerificaParanteze(char litera)
{
	if (litera == '(')
	{

		vectorToken.emplace_back(std::make_pair("token_PD", "_"));
		return true;
	}
	else if (litera == ')')
	{
		vectorToken.emplace_back(std::make_pair("token_PI", "_"));
		return true;
	}
	else if (litera == '{')
	{
		vectorToken.emplace_back(std::make_pair("token_BID", "_"));
		return true;
	}
	else if (litera == '}')
	{
		vectorToken.emplace_back(std::make_pair("token_BII", "_"));
		return true;
	}
	return false;
}

void FunctiiAnalizator::AnalizeazaLiteraCuLitera(std::string word)
{
	int i = 0;
	while (word.size() > 0)
	{
		char caracterCurent = word[i];		
		if (isalpha(word[i]) && word.size() > 0)
		{
			VerificaVariabile(word);
		}
		else if (word.size()>0 &&VerificaComentariu(word))
		{
			word.erase();
		}
		else if (word.size() > 0 && (isdigit(word[i]) || word[i] == '-' || word[i] == '+'))
		{
			VerificaNumere(word);
		}
		else if (word.size()>0 && word[i]=='"')
		{
			VerificaSirDeCaractere(word);
		}
		if (word.size() > 0&& VerificaParanteze(word[i]))
		{
			word.erase(i, 1);
		}
		else if (word.size() > 0 && VerificaPunctSiVirgula(word[i]))
		{
			word.erase(i, 1);
		}
		else if (word.size()> 0 && VerificaOperatoriNumerici(word[i]))
		{
			word.erase(i, 1);
		}
		else if (word.size() > 0)
		{
			VerificaOperatoriRelationalo(word);
		}
		

		if (caracterCurent == word[i])
		{
			std::cout << "Caracterul " << word[i] << " nu este permis si nu a fost luat in seama!\n";
			word.erase(i, 1);
		}

	}




}
bool FunctiiAnalizator::VerificaPunctSiVirgula(char litera)
{
	if (litera == ';')
	{
		vectorToken.emplace_back(std::make_pair("token_PV", "_"));
		return true;
	}
	else
		if (litera == ',')
		{
			vectorToken.emplace_back(std::make_pair("token_VG", "_"));
			return true;
		}
	return false;
}

bool FunctiiAnalizator::VerificaCuvantRezervat(std::string word)
{
	if (cuvinteCheie.find(word) != cuvinteCheie.end() && word != "main")
	{
		std::transform(word.begin(), word.end(), word.begin(), ::toupper);
		vectorToken.emplace_back(std::make_pair("token_" + word, "_)"));
		return true;
	}
	else if (cuvinteCheie.find(word) != cuvinteCheie.end() && word == "main")
	{
		std::transform(word.begin(), word.end(), word.begin(), ::toupper);
		vectorToken.emplace_back(std::make_pair("token_ID", "pointer_la_main)"));
		return true;
	}
	return false;
}

bool FunctiiAnalizator::VerificaComentariu(std::string word)
{
	bool ok = true;
	for (auto i = 0; i < word.size(); i++)
	{
		if (i == 0 && word[i] != '/')
			ok = false;
		else if (i == 1 && word[i] != '/')
			ok = false;
		else if (i > 1 && isalpha(word[i]) == false)
			ok = false;
	}
	if (ok == true)
		std::cout << "Comenatriu " << word << " a fost eliminat!\n";
	return ok;
}

void FunctiiAnalizator::VerificaOperatoriRelationalo(std::string& word)
{
	std::string op;
	for (int i = 0; i < word.size(); i++)
	{
		if (word[i] == '<' || word[i] == '>' || word[i] == '=' || word[i] == '!')
			op += word[i];
		else
			break;
	}
	int size = 0;
	if (op == "<")
	{
		size = 1;
		vectorToken.emplace_back(std::make_pair("token_OPR", "LS)"));
	}
	else if (op == ">")
	{
		size = 1;
		vectorToken.emplace_back(std::make_pair("token_OPR", "LD)"));
	}
	else if (op == "<=")
	{
		size = 2;
		vectorToken.emplace_back(std::make_pair("token_OPR", "<=)"));
	}
	else if (op == ">=")
	{
		size = 2;
		vectorToken.emplace_back(std::make_pair("token_OPR", "=>)"));
	}
	else if (op == "==")
	{
		size = 2;
		vectorToken.emplace_back(std::make_pair("token_OPR", "==)"));
	}
	else if (op == "!=")
	{
		size = 2;
		vectorToken.emplace_back(std::make_pair("token_OPR", "!=)"));
	}
	else if (op == "=")
	{
		size = 1;
		vectorToken.emplace_back(std::make_pair("token_ATR", "_"));
	}
	if (op.size() > 0)
	{
		word.erase(0, size);		
	}

}


bool FunctiiAnalizator::VerificaSirDeCaractere(std::string& word)
{
	std::string temp;

	for (int i = 0; i < word.size(); i++)
	{
		if (i == 0 && word[i] == '"')
			temp.push_back(word[i]);
		else if (i > 0 && isdigit(word[i]) == true)
			temp.push_back(word[i]);
		else if (i > 0 && isalpha(word[i]))
			temp.push_back(word[i]);
		else if (word[i] == '"' && i > 0)
			temp.push_back(word[i]);
		else
			break;

	}
	if (temp.size() > 0 && temp[temp.size() - 1] != '"' && temp[0] == '"')
	{
		std::cout << "Sirul de caractere nu a fost inchis si a fost ignorat!\n";
		word.erase(0, temp.size());
		return true;
	}

	if (temp.size() > 12)
	{
		std::cout << "Return sirul de caractere este prea marea si a fost ignorat!\n";
		word.erase(0, temp.size());
		return true;

	}
	if (temp.size() > 0)
	{

		vectorToken.emplace_back(std::make_pair("token_SIR", temp + ")"));
		word.erase(0, temp.size());
		return true;
	}
	else if (temp.size() == 0)
		return false;

}

void FunctiiAnalizator::VerificaVariabile(std::string& word)
{
	std::string cuvantTemp = ReturneazaCuvant(word);
	if (cuvantTemp.size() > 0 && VerificaCuvantRezervat(cuvantTemp))
	{
		word.erase(0, cuvantTemp.size());
	}
	else if (cuvantTemp.size() > 0 && cuvantTemp.size() <= 10)
	{
		vectorToken.emplace_back(std::make_pair("token_ID", "pointer_la_" + cuvantTemp));

		hashIndentificatori["token_ID", "pointer_la_" + cuvantTemp]++;
		word.erase(0,cuvantTemp.size());
		
	}
	else if (cuvantTemp.size() > 10)
	{
		std::cout << "Erroare numele indentificatorului " << cuvantTemp << " este prea mare!\n";
		word.erase(0, cuvantTemp.size());
	}


}

void FunctiiAnalizator::VerificaNumere(std::string& word)
{
	std::string numarReturnat = ReturneazaNumar(word);
	if (numarReturnat.size() > 0)
	{
		vectorToken.emplace_back(std::make_pair("token_NUM", numarReturnat));
		word.erase(0, numarReturnat.size());
	}
	
}

std::string FunctiiAnalizator::ReturneazaCuvant(std::string& word)
{
	std::string cuvantReturnat;
	for (int i = 0; i < word.size(); i++)
	{
		if (isalpha(word[i]) || (isdigit(word[i]) && i > 0 && cuvantReturnat.size() > 0))
			cuvantReturnat += word[i];
		else
			break;
	}
	return cuvantReturnat;
}

std::string FunctiiAnalizator::ReturneazaNumar(std::string word)
{
	std::string cuvantReturnat;
	for (int i = 0; i < word.size(); i++)
	{
		if (isdigit(word[i]) || word[i] == '.')
			cuvantReturnat += word[i];

		else if ((word[i] == 'E' && i > 0) || (word[i] == 'e' && i > 0))
			cuvantReturnat += word[i];

		else if (i > 0 && word[i - 1] == 'E' && word[i] == '+')
			cuvantReturnat += word[i];

		else if (i > 0 && word[i - 1] == 'e' && word[i] == '+')
			cuvantReturnat += word[i];

		else if (i > 0 && word[i - 1] == 'e' && word[i] == '-')
			cuvantReturnat += word[i];

		else if (i > 0 && word[i - 1] == 'E' && word[i] == '-')
			cuvantReturnat += word[i];
		else if (word[i] == '+' && vectorToken[vectorToken.size() - 1].first == "token_ATR")
		{
			cuvantReturnat.push_back(word[i]);
		}
		else if (word[i] == '-' && vectorToken[vectorToken.size() - 1].first == "token_ATR")
		{
			cuvantReturnat.push_back(word[i]);
		}
		else break;

	}
	return cuvantReturnat;
}

void FunctiiAnalizator::afiseazaVector()
{
	for (auto index : vectorToken)
	{
		std::cout << "(" << index.first << "," << index.second << ")\n";
	}
}

void FunctiiAnalizator::afiseazaHashTabel()
{
	std::cout << "\n";
	for (auto index:hashIndentificatori)
	{
		std::cout <<"(" << index.first << ")-->" << index.second << "\n";
	}
}


