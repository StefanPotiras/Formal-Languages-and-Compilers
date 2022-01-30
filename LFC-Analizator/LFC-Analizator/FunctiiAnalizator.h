#pragma once
#include<unordered_set>
#include<unordered_map>

class FunctiiAnalizator
{
public:
	
	 void AnalizatorLexical(std::ifstream &fin);
private:
	bool VerificaOperatoriNumerici(char litera);
	bool VerificaParanteze(char litera);
	void AnalizeazaLiteraCuLitera(std::string word);
	bool CheckForMain(std::string& word);
	bool VerificaPunctSiVirgula(char litera);
	bool VerificaCuvantRezervat(std::string word);
	bool VerificaComentariu(std::string word);
	bool VerificaSirDeCaractere(std::string& word);


	void VerificaOperatoriRelationalo(std::string& word);
void VerificaVariabile(std::string& word);
	void VerificaNumere(std::string& word);

	std::string ReturneazaCuvant(std::string& word);
public:
	std::string ReturneazaNumar(std::string word);

	void afiseazaVector();
	void afiseazaHashTabel();
private:
	 std::unordered_set<std::string>cuvinteCheie={"while","if","else","for","minim","int","char","main"};
	 std::vector<std::pair<std::string, std::string>>vectorToken;
	 std::unordered_map<std::string, int>hashIndentificatori;
};

