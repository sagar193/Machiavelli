#include "pch.h"
#include "Koopman.h"


Koopman::Koopman()
{
}


Koopman::~Koopman()
{
}

void Koopman::act()
{
}

void Koopman::rank(int const rank)
{
	rank_ = rank;
}

int const Koopman::rank() const
{
	return rank_;
}

void Koopman::name(std::string const name)
{
	name_ = name;
}

std::string const Koopman::name() const
{
	return name_;
}

