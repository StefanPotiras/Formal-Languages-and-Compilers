#pragma once
#include<vector>
#include"Productie.h"
#include<fstream>
#include<iostream>
class Gramatica
{
public:
	Gramatica();
	Gramatica(const std::vector<char>& VN,const std::vector<char>& VT,const char& S,const std::vector<Productie> &productii);

	const void verificare();
	 std::string generareSimpla( uint8_t optiune);
	 std::pair<std::string,std::string> generareComplexa(uint8_t optiune);
	 void generateNWords(const uint8_t& optiune, const int& numberOfWords);
	void cautaProductia(Productie& curenta, const std::string& cuvant,const  bool& start);
	 int returnRandomNumber(const int& maxNumber) const;

public:

private:
	std::vector<char>m_VN, m_VT;
	char m_S;
	std::vector<Productie>m_productii;
	std::vector<Productie>m_productiiStart;
	void cautaProductia(Productie& curenta, const std::string& cuvant, bool& start) ;
	const void verificaCuvantul(const std::string& cuvant);

public:
	friend std::istream& operator>>(std::istream& fin, Gramatica& temp)
	{
		
		std::string stringTemp, stringTemp2;
		std::getline(fin, stringTemp);
		int indexProductii;
		for (int i = 0; i < stringTemp.size(); i++)
		{   if(stringTemp[i]!=' ')
			temp.m_VN.emplace_back(stringTemp[i]);
		}
		std::getline(fin, stringTemp);
		for (int i = 0; i < stringTemp.size(); i++)
		{
			if (stringTemp[i] != ' ')
			temp.m_VT.emplace_back(stringTemp[i]);
		}
		fin >> temp.m_S;
		fin >> indexProductii;
		for (int i = 0; i < indexProductii; i++)
		{
			fin >> stringTemp >> stringTemp2;
			if (stringTemp.find(temp.m_S)!=std::string::npos)
			{
				temp.m_productii.push_back(Productie(stringTemp, stringTemp2, true));
				temp.m_productiiStart.push_back(Productie(stringTemp, stringTemp2, true));
			}
			else
			{
				temp.m_productii.push_back(Productie(stringTemp, stringTemp2, false));
			}
			
		}
		return fin;
	}
	friend std::ostream& operator<<(std::ostream& out, const Gramatica& temp) 
	{
		out<< "G=({";
		for (int i = 0; i < temp.m_VN.size(); i++)
		{ if(i!= temp.m_VN.size()-1)
			out << temp.m_VN[i]<<";";
		else
			out << temp.m_VN[i];
		}
		out << "},{";
		for (int i = 0; i < temp.m_VT.size(); i++)
		{
			if (i != temp.m_VT.size() - 1)
				out << temp.m_VT[i] << ";";
			else
				out << temp.m_VT[i];
		}
		out << "},"<<temp.m_S<<",{";
		for (int i = 0; i < temp.m_productii.size(); i++)
		{ if(i!=temp.m_productii.size()-1)
			out << temp.m_productii[i]<<";";
		else
			out << temp.m_productii[i];
		}
		out << "})";
		return out;
	}
};

