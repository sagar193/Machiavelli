#include "pch.h"
#include "Dief.h"
#include "ClientInfo.h"

Dief::Dief() : CharacterCard()
{
	this->name_ = "Dief";
}


Dief::~Dief()
{
}

bool Dief::act(ClientInfo & clientInfo, std::string cmd)
{
	return false;
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

