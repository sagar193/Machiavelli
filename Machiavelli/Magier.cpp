#include "pch.h"
#include "Magier.h"


Magier::Magier() : CharacterCard()
{
	this->name_ = "Magier";
}


Magier::~Magier()
{
}

void Magier::act()
{
}

void Magier::rank(int const rank)
{
	rank_ = rank;
}

int const Magier::rank() const
{
	return rank_;
}

void Magier::name(std::string const name)
{
	name_ = name;
}

std::string const Magier::name() const
{
	return name_;
}

