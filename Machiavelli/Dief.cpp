#include "pch.h"
#include "Dief.h"


Dief::Dief()
{
}


Dief::~Dief()
{
}

void Dief::act()
{
}

void Dief::rank(int const rank)
{
	rank_ = rank;
}

int const Dief::rank() const
{
	return rank_;
}

void Dief::name(std::string const name)
{
	name_ = name;
}

std::string const Dief::name() const
{
	return name_;
}

