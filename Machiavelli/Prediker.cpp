#include "pch.h"
#include "Prediker.h"
#include "ClientInfo.h"

Prediker::Prediker(Game& game) : CharacterCard(game)
{
	this->name_ = "Prediker";
}


Prediker::~Prediker()
{
}

bool Prediker::act(ClientInfo & clientInfo, std::string cmd)
{
	return false;
}


void Prediker::rank(int const rank)
{
	rank_ = rank;
}

int const Prediker::rank() const
{
	return rank_;
}

void Prediker::name(std::string const name)
{
	name_ = name;
}

std::string const Prediker::name() const
{
	return name_;
}

