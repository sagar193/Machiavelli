#include "pch.h"
#include "Moordenaar.h"
#include "ClientInfo.h"

Moordenaar::Moordenaar() : CharacterCard()
{
	this->name_ = "Moordenaar";
}


Moordenaar::~Moordenaar()
{
}

bool Moordenaar::act(ClientInfo & clientInfo, std::string cmd)
{
	return false;
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
