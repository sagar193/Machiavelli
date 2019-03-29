#include "pch.h"
#include "Koning.h"
#include "ClientInfo.h"
#include "Game.h"
#include <algorithm>

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
	int goldRecieved = 0;
	std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard card) {
		if (card.owner() == game_.currentPlayer().ownertag() && card.color() == card.GEEL) {
			goldRecieved++;
		}

	});
	game_.currentPlayer().gold(goldRecieved + game_.currentPlayer().gold());
	game_.sendToCurrentPlayer("Je ontvangt " + std::to_string(goldRecieved) + " goud.");

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

