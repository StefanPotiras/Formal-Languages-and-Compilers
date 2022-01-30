#pragma once
#include <vector>
#include <string>
#include<unordered_set>
#include<map>
#include<unordered_map>

#include<fstream>

class AFD
{public:
	
	void readFromFile();
	void writeInCons() const;

	const int& verificaCuvantul( std::string& cuvant);
	const bool& verificaAutomatul();

	 std::string deleteL(std::string cuvant) ;

private:
	std::unordered_set<std::string>m_q;
	std::string m_sigma;

	std::unordered_set<std::string>m_finalStates;
	std::string m_initialState;

	std::map<std::pair<std::string,std::string>,std::string>m_trans;
	
	
};

