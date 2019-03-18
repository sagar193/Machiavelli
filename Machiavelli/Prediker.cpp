#include "pch.h"
#include "Prediker.h"


Prediker::Prediker() : CharacterCard{}
{
}


Prediker::~Prediker()
{
}

void Prediker::act()
{
}

void Prediker::rank(int const rank)
{
	rank_ = rank;
}

int const Prediker::rank() const
{
	return rank_;
}

void Prediker::name(std::string const name)
{
	name_ = name;
}

std::string const Prediker::name() const
{
	return name_;
}

