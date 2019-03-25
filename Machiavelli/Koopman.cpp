#include "pch.h"
#include "Koopman.h"
#include "ClientInfo.h"

Koopman::Koopman() : CharacterCard()
{
	this->name_ = "Koopman";
}


Koopman::~Koopman()
{
}

bool Koopman::act(ClientInfo & clientInfo, std::string cmd)
{
	return false;
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

