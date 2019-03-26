#include "pch.h"
#include "Condottiere.h"
#include "ClientInfo.h"

Condottiere::Condottiere(Game& game)  : CharacterCard(game)
{
	this->name_ = "Condonttiere";
	characterCardIdentifier_ = CharacterCardEnum::CONDOTTIERE;
	mugged_ = false;
}


Condottiere::~Condottiere()
{
}

bool Condottiere::act(ClientInfo & clientInfo, std::string cmd)
{
	return false;
}

void Condottiere::rank(int const rank)
{
	rank_ = rank;
}

int const Condottiere::rank() const
{
	return rank_;
}

void Condottiere::name(std::string const name)
{
	name_ = name;
}

std::string const Condottiere::name() const
{
	return name_;
}

