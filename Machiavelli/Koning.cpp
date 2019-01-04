#include "pch.h"
#include "Koning.h"


Koning::Koning()
{
}


Koning::~Koning()
{
}

void Koning::act()
{
}

void Koning::rank(int const rank)
{
	rank_ = rank;
}

int const Koning::rank() const
{
	return rank_;
}

void Koning::name(std::string const name)
{
	name_ = name;
}

std::string const Koning::name() const
{
	return name_;
}

