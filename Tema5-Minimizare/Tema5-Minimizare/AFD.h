#pragma once
#include <vector>
#include <string>
#include<unordered_set>
#include<set>
#include<map>
#include<unordered_map>

#include<fstream>

class AFD
{
public:

	void readFromFile();
	void writeInCons() const;

	const int& verificaCuvantul(std::string& cuvant);
	const bool& verificaAutomatul();
	void deleteInacTrans();
	void createMatrix();

	bool duceInPerecheMarcata(std::pair<std::string,std::string>,std::set<std::pair<std::string, std::string>>&);

	void marcheazaVector(std::vector<std::string>&vectorCurent);

	std::string deleteL(std::string cuvant);
	void writeInFile();
private:
	std::string returnString(int initial, int end, std::string string);
	void deleteTranz(std::set<std::pair<std::string, std::string>>perechi);
	
private:
	std::unordered_set<std::string>m_q;
	std::unordered_set<std::string>m_sigma;

	std::unordered_set<std::string>m_finalStates;
	std::string m_initialState;

	std::map<std::pair<std::string, std::string>, std::string>m_trans;


};

