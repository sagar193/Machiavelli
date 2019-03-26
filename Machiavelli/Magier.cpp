#include "pch.h"
#include "Magier.h"
#include "ClientInfo.h"

Magier::Magier(Game& game) : CharacterCard(game)
{
	this->name_ = "Magier";
	characterCardIdentifier_ = CharacterCardEnum::MAGIER;
	mugged_ = false;
}


Magier::~Magier()
{
}

bool Magier::act(ClientInfo & clientInfo, std::string cmd)
{
	return false;
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

