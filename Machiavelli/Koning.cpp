#include "pch.h"
#include "Koning.h"
#include "ClientInfo.h"
#include "Game.h"

Koning::Koning(Game& game) : CharacterCard(game)
{
	this->name_ = "Koning";
	characterCardIdentifier_ = CharacterCardEnum::KONING;
	mugged_ = false;
}


Koning::~Koning()
{
}

void Koning::onEnter()
{
	game_.client1().get_player().isKing(false);
	game_.client2().get_player().isKing(false);
	game_.currentPlayer().isKing(true);
	game_.sendToCurrentPlayer("De volgende ronde zal jij koning zijn.");
	game_.sendToCurrentPlayer("Druk een toets om door te gaan.");
}

void Koning::onLeave()
{
	mugged_ = false;
}

bool Koning::act(ClientInfo & clientInfo, std::string cmd)
{
	return true;
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

