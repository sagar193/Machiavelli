#include "pch.h"
#include "Moordenaar.h"


Moordenaar::Moordenaar() : CharacterCard{}
{
}


Moordenaar::~Moordenaar()
{
}

void Moordenaar::act()
{
}

void Moordenaar::rank(int const rank)
{
	rank_ = rank;
}

int const Moordenaar::rank() const
{
	return rank_;
}

void Moordenaar::name(std::string const name)
{
	name_ = name;
}

std::string const Moordenaar::name() const
{
	return name_;
}
