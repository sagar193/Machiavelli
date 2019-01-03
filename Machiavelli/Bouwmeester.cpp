#include "pch.h"
#include "Bouwmeester.h"


Bouwmeester::Bouwmeester()
{
}


Bouwmeester::~Bouwmeester()
{
}

void Bouwmeester::act()
{
}

void Bouwmeester::rank(int const rank)
{
	rank_ = rank;
}

int const Bouwmeester::rank() const
{
	return rank_;
}

void Bouwmeester::name(std::string const name)
{
	name_ = name;
}

std::string const Bouwmeester::name() const
{
	return name_;
}
