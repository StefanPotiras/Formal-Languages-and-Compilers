#include "AFD.h"
#include<iostream>
void AFD::readFromFile()
{
	int number;
	std::ifstream in("data.in");
	/*in >> number;
	for (int i = 0; i < number; i++)
	{
		std::string temp;
		in >> temp;
		m_q.insert(temp);
	}*/
	//in >> m_sigma;

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
		m_trans[std::make_pair(start,q)]=fin;
	}
}

void AFD::writeInCons() const
{
	
	std::cout<< "M=({";
	int i = 0;
	for (auto& index:m_q)
	{
		i++;
		if(i<m_q.size())
		std::cout << index<<",";
		else
			std::cout << index<<"},{";
	}

	for (int i = 0; i < m_sigma.size(); i++)
	{
		if (i < m_sigma.size()-1)
			std::cout << m_sigma[i] << ",";
		else
			std::cout << m_sigma[i] << "},Sg,"<<m_initialState<<",{";
	}
	int y = 0;
	for (auto& index:m_finalStates)
	{
		y++;
		if (y < m_finalStates.size())
			std::cout << index << ",";
		else
			std::cout << index << "})"<<"\n";
	}

	for (auto& index:m_trans )
	{
		std::cout << index.first.first << "->" << index.first.second<<"-->"<< index.second << "\n";
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


const int& AFD::verificaCuvantul( std::string& cuvant) 
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
	/*if (m_q.find(m_initialState) == m_q.end())
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
		else if (m_sigma.find(index.first.second) == std::string::npos)
			return false;

	}
	return true;*/
	std::unordered_set<std::string>frecventa;
	for (auto& index:m_trans)
	{
		if (m_q.find(index.second) != m_q.end())
			m_q.insert(index.second);

		if(m_q.find(index.first.first) != m_q.end())
			m_q.insert(index.first.first);

		if(frecventa.find(index.first.second)!=frecventa.end())
		frecventa.insert(index.first.second);
	}
	for (auto& index:frecventa)
	{
		m_sigma += index;
	}
	return true;
}
