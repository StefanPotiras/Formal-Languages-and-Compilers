#include "Productie.h"
#include<iostream>
void Productie::citesteProductie()
{
	std::cin >> m_left;
	std::cin >> m_right;
}

Productie::Productie()
	:m_left("")
	,m_right("")
	,m_start("")
{}

Productie::Productie(const std::string& left, const std::string& right, const bool& start)
	:m_left(left)
	,m_right(right)
	,m_start(start)
{}

const std::string& Productie::getLeft() const
{
	return m_left;
}

const std::string& Productie::getRight() const
{
	return m_right;
}

const bool Productie::getStart() const
{
	return m_start;
}

//bool Productie::getUsed() const
//{
//	return m_used;
//}
//
//void Productie::setUded(const bool& used)
//{
//	m_used = used;
//}
