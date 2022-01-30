#pragma once
#include<string>
#include<iostream>
class Productie
{ public:
	void citesteProductie();
	Productie();
	Productie(const std::string &left,const std::string &right,const bool& start);

	const std::string& getLeft()const;
	const std::string& getRight()const;
	const bool getStart() const;
	//bool getUsed() const;
	//void setUded(const bool& used);
	friend std::ostream& operator<<(std::ostream& r, const Productie& temp)
	{
		r << temp.m_left;
		std::cout << "->";
		r<< temp.m_right;
		return r;
	}

private:
	std::string m_left;
	std::string m_right;
	bool m_start;
};

