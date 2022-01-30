#include "AFN.h"
#include<stack>
#include<map>
void AFN::readFromFile()
{
	int number;
	std::ifstream in("data.in");
	in >> number;
	for (int i = 0; i < number; i++)
	{
		std::string temp;
		in >> temp;
		m_q.insert(temp);
	}
	in >> m_sigma;

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
	int n_st;
	
	for (int i = 0; i < n_tranzitii; i++)
	{
		std::vector<std::string>trans;
		in >> start >> q >> n_st;
		for (int i = 0; i < n_st; i++)
		{
			in >> fin;
			trans.push_back(fin);
		}
		m_trans[std::make_pair(start, q)] = trans;
	}
}

void AFN::writeInCons() const
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

	for (int i = 0; i < m_sigma.size(); i++)
	{
		if (i < m_sigma.size() - 1)
			std::cout << m_sigma[i] << ",";
		else
			std::cout << m_sigma[i] << "},Sg," << m_initialState << ",{";
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
		std::cout << index.first.first << "->" << index.first.second << "-->";
		for (auto& index2 : index.second)
		{
			std::cout << index2 << " ";
		}
		std::cout << "\n";
	}
}

std::string AFN::deleteL(std::string cuvant)
{
	for (int position = 0; position < cuvant.length(); ++position) {
		if (cuvant[position] == '@') {
			cuvant.erase(position, 1);
		}
	}
	return cuvant;
}

std::string AFN::returneazaCuvantul( std::string cuvant,  int numarLitere)
{
	cuvant.erase(0, numarLitere);
	return cuvant;
}



int AFN::backTr(std::string& cuvant)
{
	std::stack<std::pair<std::string, std::string>>stivaEvolutie;
	std::map<std::pair<std::string, std::string>, std::vector<std::string>>mapElementeFolosite;

	int ok = verificaCuvantul(cuvant,m_initialState,stivaEvolutie,mapElementeFolosite);
	
	while (!stivaEvolutie.empty() && ok!=1)
	{
		std::pair < std::string, std::string>pairCurent = stivaEvolutie.top();
		std::pair<std::string, std::string>stareCurenta;

		stareCurenta.first = pairCurent.first;
		stareCurenta.second = pairCurent.second[0];

		if (mapElementeFolosite[pairCurent].size() < m_trans[stareCurenta].size())
		{

			std::string stare = m_trans[stareCurenta][mapElementeFolosite[pairCurent].size()];
			mapElementeFolosite[pairCurent].push_back(stare);

			int okCurent= verificaCuvantul(returneazaCuvantul(pairCurent.second, 1), stare, stivaEvolutie, mapElementeFolosite);
			if (ok == -1 && okCurent == -1)
			{
				ok = okCurent;
			}
			else if (ok != -1 && okCurent != -1)
				ok = okCurent;
			
		}
		else
			stivaEvolutie.pop();

	}
	return ok;
}
const int& AFN::verificaCuvantul(std::string cuvant,std::string stareInitiala,std::stack<std::pair<std::string, std::string>>&stivaEvolutie,
	std::map<std::pair<std::string, std::string>, std::vector<std::string>>&mapElementeFolosite)
{  
	std::string currentState = stareInitiala;
	std::string nextState = "";
	//cuvant = deleteL(cuvant);

	for (int i = 0; i <cuvant.size(); i++)
	{
		
		std::pair<std::string, std::string>state;
		state.first = currentState;
		state.second = cuvant[i];
		
		if(m_trans[state].size()!=0)
		nextState = m_trans[state][0];
		if (m_trans[state].size() > 1)
		{
			stivaEvolutie.push(std::make_pair(currentState, returneazaCuvantul(cuvant, i)));
		}
		state.second = returneazaCuvantul(cuvant, i);
		if(std::find(mapElementeFolosite[state].begin(), mapElementeFolosite[state].end(),nextState)== mapElementeFolosite[state].end())
		mapElementeFolosite[state].push_back(nextState);
		
	
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

const bool& AFN::verificaAutomatul()
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

	for (auto& index : m_trans)
	{
		if (m_q.find(index.first.first) == m_q.end())
			return false;
		else if (m_sigma.find(index.first.second) == std::string::npos)
			return false;
		for (auto& indexSt : index.second)
		{
			if (m_q.find(indexSt) == m_q.end())
				return false;
		}
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
	return true;
}
