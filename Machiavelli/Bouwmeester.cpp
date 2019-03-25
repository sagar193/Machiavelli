#include "pch.h"
#include "Bouwmeester.h"
#include "ClientInfo.h"

Bouwmeester::Bouwmeester() : CharacterCard()
{
	this->name_ = "Bouwmeester";
}


Bouwmeester::~Bouwmeester()
{
}

bool Bouwmeester::act(ClientInfo & clientInfo, std::string cmd)
{
	return false;
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
