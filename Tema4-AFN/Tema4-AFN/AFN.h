#pragma once
#include <vector>
#include <string>
#include<unordered_set>
#include<map>
#include<unordered_map>
#include<iostream>
#include<fstream>
#include<stack>
class AFN
{
public:

	void readFromFile();
	void writeInCons() const;

	int backTr(std::string& cuvant);
	const int& verificaCuvantul(std::string cuvant, std::string stareInitiala,std::stack<std::pair<std::string, std::string>>&stivaEvolutie,
		std::map<std::pair<std::string, std::string>, std::vector<std::string>>& mapElementeFolosite);
	const bool& verificaAutomatul();

	std::string deleteL(std::string cuvant);

private:
	std::string returneazaCuvantul(std::string cuvant, int numarLitere);
	

	std::unordered_set<std::string>m_q;
	std::string m_sigma;

	std::unordered_set<std::string>m_finalStates;
	std::string m_initialState;

	std::map<std::pair<std::string, std::string>, std::vector<std::string>>m_trans;
};

