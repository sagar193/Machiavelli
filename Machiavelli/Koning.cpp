#include "pch.h"
#include "Koning.h"
#include "ClientInfo.h"

Koning::Koning(Game& game) : CharacterCard(game)
{
	this->name_ = "Koning";
	characterCardIdentifier_ = CharacterCardEnum::KONING;
	mugged_ = false;
}


Koning::~Koning()
{
}

bool Koning::act(ClientInfo & clientInfo, std::string cmd)
{
	return false;
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

