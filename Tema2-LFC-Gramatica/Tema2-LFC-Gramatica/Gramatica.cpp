#include "Gramatica.h"
#include<algorithm>
#include<random>
#include<unordered_set>
#include<regex>
int i = 1;
Gramatica::Gramatica()
	:m_VN()
	, m_VT()
	, m_S()
	, m_productii()
{}

Gramatica::Gramatica(const std::vector<char>& VN, const std::vector<char>& VT, const char& S, const std::vector<Productie>& productii)
	:m_VN(VN)
	, m_VT(VT)
	, m_S(S)
	, m_productii(productii)
{}
const void Gramatica::verificare()
{
	int nr = 0;
	bool check = true;
	if (std::find_first_of(m_VN.begin(), m_VN.end(), m_VT.begin(), m_VT.end()) != m_VN.end())
	{
		check = false;
		std::cout << "VN se intersecreaza cu VT!" << "\n";
	}
	else if (std::find(m_VN.begin(), m_VN.end(), m_S) == m_VN.end())
	{
		check = false;
		std::cout << "S nu apartinelu VN" << "\n";
	}
	for (auto index : m_productii)
	{
		if (std::find_first_of(m_VN.begin(), m_VN.end(), index.getLeft().begin(), index.getLeft().end()) == m_VN.end())
		{
			check = false;
			std::cout << "Pentru fiecare regula membru stang nu contine cel putin un neterminal!" << "\n";
			break;
		}
	}
	for (auto index : m_productii)
	{
		if (std::find(index.getLeft().begin(), index.getLeft().end(), m_S) != index.getLeft().end() && index.getLeft().size() == 1)
		{
			nr++;
		}
	}

	if (nr<0)
	{
		check = false;
		std::cout << "NU exista cel putin o productie care are in stanga doar S!" << "\n";
	}
	for (auto index : m_productii)
	{
		for (auto left : index.getLeft())
		{
			if (std::find(m_VN.begin(), m_VN.end(), left) == m_VN.end() && std::find(m_VT.begin(), m_VT.end(), left) == m_VT.end())
			{
				check = false;
				std::cout << "Fiecare productie NU contine doar elemente din VN si VT!" << "\n";
				break;
			}

		}
		for (auto right : index.getRight())
		{
			if (std::find(m_VN.begin(), m_VN.end(), right) == m_VN.end() && std::find(m_VT.begin(), m_VT.end(), right) == m_VT.end())
			{
				check = false;
				std::cout << "Fiecare productie NU contine doar elemente din VN si VT!" << "\n";
				break;
			}

		}

	}
	for (auto& vt : m_VT)
	{
		bool ok = false;
		for (auto& prod : m_productii)
		{
			if (std::find(prod.getLeft().begin(), prod.getLeft().end(), vt) != prod.getLeft().end() || std::find(prod.getRight().begin(), prod.getRight().end(), vt) != prod.getRight().end())
			{
				ok = true;
			}
		}
		if (ok == false)
		{
			check = false;
			std::cout << "Elementele din VT nu se gases in Productii!"<<"\n";
			break;
		}
	}
	for (auto& vt : m_VN)
	{
		bool ok = false;
		for (auto& prod : m_productii)
		{
			if (std::find(prod.getLeft().begin(), prod.getLeft().end(), vt) != prod.getLeft().end() || std::find(prod.getRight().begin(), prod.getRight().end(), vt) != prod.getRight().end())
			{
				ok = true;
			}
		}
		if (ok == false)
		{
			check = false;
			std::cout << "Elementele din VN nu se gasesc in Productii!";
			break;
			
		}
	}
	if (check == true)
	{
		std::cout << "Gramatica introdusa respecta toate conditiile!" << "\n\n";
	}
}

const void Gramatica::verificaCuvantul(const std::string& cuvant)
{
	bool ok = true;
	for (auto index:cuvant)
	{
		if (std::find(m_VT.begin(), m_VT.end(), index) == m_VT.end())
		{
			ok = false;
		}
	}
	if (ok == false)
	{
		std::cout <<i<<".Cuvantul: " << cuvant << "--->"<< "Nu este format doar din terminale" << "\n";
		i++;
	}
	else if (ok == true)
	{
		std::cout <<i<<".Cuvantul: " << cuvant << "--->" << "este format doar din terminale" << "\n";
		i++;
	}
}
 int Gramatica::returnRandomNumber(const int& maxNumber) const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, maxNumber);
	return dis(gen);
}
std::pair<std::string, std::string> Gramatica::generareComplexa(uint8_t optiune)
{
	std::string sirEvolutie;
	std::string cuvant;
	bool start = true;
	Productie startProd;

	startProd = m_productiiStart[returnRandomNumber(m_productiiStart.size() - 1)];
	cuvant = startProd.getRight();
	while (start)
	{
		sirEvolutie += cuvant;
		sirEvolutie += "->";

		Productie productieCurenta;
		cautaProductia(productieCurenta, cuvant, start);

		if (start == true && productieCurenta.getRight() != "*")
		{
			auto i = cuvant.find(productieCurenta.getLeft());
			cuvant.erase(i, productieCurenta.getLeft().size());
			cuvant.insert(i, productieCurenta.getRight());
		}
		if (start == true && productieCurenta.getRight() == "*")
		{
			auto i = cuvant.find(productieCurenta.getLeft());
			cuvant.erase(i, productieCurenta.getLeft().size());
		}
		else if (start == false)
		{
			break;
		}
	}
	return std::make_pair(cuvant,sirEvolutie);
}

void Gramatica::generateNWords(const uint8_t& optiune, const int& numberOfWords)
{ 
	std::unordered_set<std::string>words;
	int numar = 1;
	
	while (words.size()!=numberOfWords)
	{
		if (optiune == 0)
		{
			words.insert(generareSimpla(0));
		}
		else if(optiune==1)
		{
			std::pair<std::string, std::string>temp=generareComplexa(1);
			if (words.count(temp.first) == 0)
			{
				temp.second.resize(temp.second.size() - 2);
				std::cout << numar << "." << temp.second << "\n";
				words.insert(temp.first);
				numar++;
			}
			
		}
		
	}
	
	for (auto& index:words)
	{
		verificaCuvantul(index);
	}
}
 std::string Gramatica::generareSimpla( uint8_t optiune)
{	
	std::string cuvant;
	bool start = true, corect = true;
	cuvant = m_productiiStart[returnRandomNumber(m_productiiStart.size() - 1)].getRight();
	if (optiune == 0)
	{	
		while (start)
		{
			Productie productieCurenta;
			cautaProductia(productieCurenta, cuvant, start);
			if (start == true && productieCurenta.getRight()!="*")
			{
				auto i = cuvant.find(productieCurenta.getLeft());
				cuvant.erase(i, productieCurenta.getLeft().size());
				cuvant.insert(i, productieCurenta.getRight());
			}
			if (start == true && productieCurenta.getRight() == "*")
			{
				auto i = cuvant.find(productieCurenta.getLeft());
				cuvant.erase(i, productieCurenta.getLeft().size());
			}
			else if(start==false)
			{
				break;
			}
		}		
		
	}
	return cuvant;
}

 
void Gramatica::cautaProductia(Productie& curenta, const std::string& cuvant, bool& start)
{
	std::vector<int>productiiAplicabile;
	for (int i=0;i<m_productii.size();i++)
	{
		if (cuvant.find(m_productii[i].getLeft()) != std::string::npos )
		{
			productiiAplicabile.emplace_back(i);
		}
	}
	
	if (productiiAplicabile.size() == 0)
		start = false;
	else
	{
		curenta = m_productii[productiiAplicabile[returnRandomNumber(productiiAplicabile.size() - 1)]];
	}
	
}












