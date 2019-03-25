#include "pch.h"
#include "Prediker.h"
#include "ClientInfo.h"
#include "Game.h"
#include <string>

Prediker::Prediker(Game& game) : CharacterCard(game)
{
	this->name_ = "Prediker";
}


Prediker::~Prediker()
{
}

void Prediker::onEnter()
{
	auto& player = game_.currentClient();
	game_.sendToCurrentPlayer("de prediker krijgt voor elk blauw gebouw 1 goudstuk");
	auto count = 0;
	std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard& card) 
	{
		if (card.color() == card.BLAUW && card.owner() == player.get_player().ownertag()) {
			count++;
		}
	});
	
	game_.sendToCurrentPlayer("je bezit " + std::to_string(count) + " blauwe gebouwen");
	player.get_player().gold(player.get_player().gold() + count);
	game_.sendToCurrentPlayer("je bezit nu " + std::to_string(player.get_player().gold()) + " blauwe gebouwen");
	game_.sendToCurrentPlayer("druk op enter om verder te gaan");
}

bool Prediker::act(ClientInfo & clientInfo, std::string cmd)
{
	return true;
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

void Prediker::removeBuildingCard(int index)
{
	game_.sendToCurrentPlayer("de gebouwen van de prediker kunnen niet verwijderd worden");
}

