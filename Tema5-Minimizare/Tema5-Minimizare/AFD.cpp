#include "AFD.h"
#include<iostream>
#include <sstream>
#include <stack>
#include <set>
void AFD::readFromFile()
{
	int number;
	std::ifstream in("Text.txt");
	in >> number;
	for (int i = 0; i < number; i++)
	{
		std::string temp;
		in >> temp;
		m_q.insert(temp);
	}
	in >> number;
	for (int i = 0; i < number; i++)
	{
		std::string temp;
		in >> temp;
		m_sigma.insert(temp);
	}

	in >> m_initialState;

	int n_finalStates;
	in >> n_finalStates;

	for (int i = 0; i < n_finalStates; i++)
	{
		std::string finalState;
		in >> finalState;
		m_finalStates.insert(finalState);
	}

	int n_tranzitii;
	in >> n_tranzitii;
	std::string start, q, fin;
	for (int i = 0; i < n_tranzitii; i++)
	{
		in >> start >> q >> fin;
		m_trans[std::make_pair(start, q)] = fin;
	}
}

void AFD::writeInCons() const
{

	std::cout << "M=({";
	int i = 0;
	for (auto& index : m_q)
	{
		i++;
		if (i < m_q.size())
			std::cout << index << ",";
		else
			std::cout << index << "},{";
	}
	int p = 0;
	for (auto index : m_sigma)
	{
		p++;
		if (p < m_sigma.size())
			std::cout << index << ",";
		else
			std::cout << index << "},Sg," << m_initialState << ",{";
	}
	int y = 0;
	for (auto& index : m_finalStates)
	{
		y++;
		if (y < m_finalStates.size())
			std::cout << index << ",";
		else
			std::cout << index << "})" << "\n";
	}

	for (auto& index : m_trans)
	{
		std::cout << index.first.first << "->" << index.first.second << "-->" << index.second << "\n";
	}
}

std::string AFD::deleteL(std::string cuvant)
{
	for (int position = 0; position < cuvant.length(); ++position) {
		if (cuvant[position] == '@') {
			cuvant.erase(position, 1);
		}
	}
	return cuvant;
}

void AFD::writeInFile()
{
	int i = 0;
	std::map<std::string, std::string>mapElemente;
	int sizeQ = m_q.size();
	for (auto index:m_q)
	{
		mapElemente[index] = "r" + std::to_string(i);
		index = "r" + std::to_string(i);
	
		i++;
	}
	m_q.clear();
	for (int j = 0; j < sizeQ; j++)
	{
		m_q.insert("r"+ std::to_string(j));
	}
	m_initialState = "r0";

	std::vector<std::string>temp;
	for (auto index:m_finalStates)
	{
		temp.push_back(mapElemente[index]);

	}
	m_finalStates.clear();
	for (auto index:temp)
	{
		m_finalStates.insert(index);
	}
	std::set<std::pair<std::string, std::string>>trans;
	for (auto index:m_trans)
	{	
			std::pair<std::string, std::string>pereche;
			pereche.first = mapElemente[index.first.first];
			pereche.second = index.first.second;
			if(pereche.first!="")
			m_trans[pereche] = mapElemente[index.second];
			if (index.first.first[0] == 'q')
				trans.insert(index.first);
	}
	for (auto index:trans)
	{
		m_trans.erase(index);
	}
	
	std::ofstream out("data.out");
	out << m_q.size() << "\n";
	for (auto& index : m_q)
	{
		out << index << " ";
	}
	out << "\n" << m_sigma.size() << "\n";
	for (auto& index : m_sigma)
	{
		out << index << " ";
	}
	out << "\n" << m_initialState << "\n";
	out << m_finalStates.size() << "\n";

	for (auto& index : m_finalStates)
	{
		out << index << " ";
	}

	out << "\n" << m_trans.size() << "\n";
	for (auto& index : m_trans)
	{
		out << index.first.first << " " << index.first.second << " " << index.second << "\n";
	}

}

std::string AFD::returnString(int initial, int end, std::string string)
{
	return string.erase(initial, end);
}

void AFD::deleteTranz(std::set<std::pair<std::string, std::string>>perechi)
{
	for (auto index : perechi)
	{
		std::unordered_set<std::string>temp;

		temp.insert(index.second);
		m_q.erase(index.second);

		if (m_finalStates.find(index.second) != m_finalStates.end())
			m_finalStates.erase(index.second);

		for (auto index2 : perechi)
		{
			if (index2 != index && index2.first == index.first)
			{
				temp.insert(index2.second);
				m_q.erase(index2.second);
				if (m_finalStates.find(index2.second) != m_finalStates.end())
					m_finalStates.erase(index2.second);
			}
		}

		for (auto& trnz : m_trans)
		{
			if (temp.find(trnz.second) != temp.end())
			{
				trnz.second = index.first;
			}
		}

		for (auto it = m_trans.begin(); it != m_trans.end();)
		{
			if (temp.find(it->first.first) != temp.end() && m_trans.find(std::make_pair(index.first, it->first.second)) == m_trans.end())
			{


				auto retineTemp = m_trans.extract(it->first);
				retineTemp.key() = std::make_pair(index.first, it->first.second);
				m_trans.insert(std::move(retineTemp));
				it++;

			}
			else if (temp.find(it->first.first) != temp.end() && m_trans.find(std::make_pair(index.first, it->first.second)) != m_trans.end())
			{

				it = m_trans.erase(it);
			}
			else it++;
		}

	}


}

void AFD::deleteInacTrans()
{
	std::stack<std::string>stackBFS;
	stackBFS.push(m_initialState);
	std::vector<std::string>visitedTrans;

	while (!stackBFS.empty())
	{
		std::string curentTrans = stackBFS.top();
		stackBFS.pop();

		if (std::find(visitedTrans.begin(), visitedTrans.end(), curentTrans) == visitedTrans.end())
			visitedTrans.push_back(curentTrans);


		for (auto index : m_sigma)
		{
			std::string temp = "";
			std::pair<std::string, std::string> pairTrans;
			pairTrans.first = curentTrans;
			pairTrans.second = index;
			if (m_trans.find(pairTrans) != m_trans.end())
				temp = m_trans[pairTrans];

			if (temp != "")
			{
				if (std::find(visitedTrans.begin(), visitedTrans.end(), temp) == visitedTrans.end())
					stackBFS.push(temp);
			}
		}
	}

	for (auto it = m_q.begin(); it != m_q.end();)
	{
		if (std::find(visitedTrans.begin(), visitedTrans.end(), *it) == visitedTrans.end())
		{

			for (auto sigma : m_sigma)
			{
				std::string temp = "";
				std::string incercare = *it;
				std::pair<std::string, std::string> pairTrans(*it, sigma);

				if (m_trans.find(pairTrans) != m_trans.end())
				{
					m_trans.erase(pairTrans);
				}
			}
			it = m_q.erase(it);
		}
		else it++;
	}

}


void AFD::createMatrix()
{
	std::vector<std::vector<std::string>>matrixTrans;
	matrixTrans.resize(m_q.size());
	for (int i = 0; i < matrixTrans.size(); i++)
		matrixTrans[i].resize(i + 1);

	std::unordered_set<std::string>::iterator it;
	it = m_q.begin();

	for (int i = 0; i < matrixTrans.size(); i++)
	{

		matrixTrans[i][matrixTrans[i].size() - 1] = *it;
		it++;
		for (int j = 0; j < matrixTrans[i].size() - 1; j++)
		{
			matrixTrans[i][j] = "_";
		}

	}

	std::set<std::pair<std::string, std::string>>perechiMarcate;
	std::set<std::pair<std::string, std::string>>perechiNemarcate;

	while (true)
	{
		int sizeM = perechiMarcate.size();
		for (int i = 0; i < matrixTrans.size(); i++)
		{
			for (int j = i + 1; j < matrixTrans.size(); j++)
			{

				std::string state1 = matrixTrans[i][matrixTrans[i].size() - 1];
				std::string state2 = matrixTrans[j][matrixTrans[j].size() - 1];
				perechiNemarcate.insert(std::make_pair(state1, state2));

				if (m_finalStates.find(state1) != m_finalStates.end() && m_finalStates.find(state2) == m_finalStates.end() &&
					perechiMarcate.find(std::make_pair(state1, state2)) == perechiMarcate.end())
				{
					matrixTrans[j][i] = "X";
					perechiMarcate.insert(std::make_pair(state1, state2));
				}

				else if (m_finalStates.find(state2) != m_finalStates.end() && m_finalStates.find(state1) == m_finalStates.end() &&
					perechiMarcate.find(std::make_pair(state1, state2)) == perechiMarcate.end())
				{
					matrixTrans[j][i] = "X";
					perechiMarcate.insert(std::make_pair(state1, state2));

				}

				else if (duceInPerecheMarcata(std::make_pair(state1, state2), perechiMarcate))
					matrixTrans[j][i] = "X";

			}
			

		}

		if (perechiMarcate.size() == sizeM)
			break;
	}

	for (auto index : perechiMarcate)
	{
		perechiNemarcate.erase(index);
	}


	deleteTranz(perechiNemarcate);

	for (int i = 0; i < matrixTrans.size(); i++)
	{
		for (auto index2 : matrixTrans[i])
			std::cout << index2 << " ";
		std::cout << "\n";
	}


}

bool AFD::duceInPerecheMarcata(std::pair<std::string, std::string>perecheCurenta, std::set<std::pair<std::string, std::string>>& perechiMarcate)
{

	for (auto index : m_sigma)
	{
		std::string stringPereche1 = "";
		std::string stringPereche2 = "";
		std::pair<std::string, std::string>pair1;
		pair1.first = perecheCurenta.first;
		pair1.second = index;
		stringPereche1 = m_trans[pair1];

		std::pair<std::string, std::string>pair2;
		pair2.first = perecheCurenta.second;
		pair2.second = index;
		stringPereche2 = m_trans[pair2];

		if (perechiMarcate.find(std::make_pair(stringPereche1, stringPereche2)) != perechiMarcate.end() || 
			perechiMarcate.find(std::make_pair(stringPereche2, stringPereche1)) != perechiMarcate.end())
		{
			perechiMarcate.insert(perecheCurenta);
			return true;
		}

	}
	return false;
}

void AFD::marcheazaVector(std::vector<std::string>& vectorCurent)
{
}


const int& AFD::verificaCuvantul(std::string& cuvant)
{
	std::string currentState = m_initialState;
	std::string nextState = "";
	cuvant = deleteL(cuvant);

	for (int i = 0; i < cuvant.size(); i++)
	{
		std::cout << cuvant[i] << "\n";
		std::pair<std::string, std::string>state;
		state.first = currentState;
		state.second = cuvant[i];

		nextState = m_trans[state];

		if (!nextState.length())
		{
			return -1;
		}
		else
		{
			currentState = nextState;
			nextState = "";
		}

	}
	if (m_finalStates.find(currentState) != m_finalStates.end())
	{
		return 1;
	}
	else if (m_finalStates.find(currentState) == m_finalStates.end())
		return 0;
}
//Complexitatea este O(lungimea cuvantului) 
const bool& AFD::verificaAutomatul()
{
	if (m_q.find(m_initialState) == m_q.end())
	{
		return false;
	}

	for (auto& index:m_finalStates)
	{
		if (m_q.find(index) == m_q.end())
		{
			return false;
		}
	}

	for (auto& index:m_trans)
	{
		if (m_q.find(index.first.first) == m_q.end())
			return false;
		else if (m_q.find(index.second) == m_q.end())
			return false;
		else if (m_sigma.find(index.first.second) == m_sigma.end())
			return false;

	}
	return true;
	/*std::unordered_set<std::string>frecventa;
	for (auto& index : m_trans)
	{
		if (m_q.find(index.second) != m_q.end())
			m_q.insert(index.second);

		if (m_q.find(index.first.first) != m_q.end())
			m_q.insert(index.first.first);

		if (frecventa.find(index.first.second) != frecventa.end())
			frecventa.insert(index.first.second);
	}
	for (auto& index : frecventa)
	{
		m_sigma += index;
	}*/

}
