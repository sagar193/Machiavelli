#include "pch.h"
#include "Prediker.h"
#include "ClientInfo.h"
#include "Game.h"
#include <string>

Prediker::Prediker(Game& game) : CharacterCard(game)
{
	this->name_ = "Prediker";
	characterCardIdentifier_ = CharacterCardEnum::PREDIKER;
	mugged_ = false;
	used_ = false;
}


Prediker::~Prediker()
{
}

void Prediker::onEnter()
{
	if (used_) {
		game_.sendToCurrentPlayer("deze kaart is al gebruikt druk op enter om verder te gaan");
		return;
	}
	auto& player = game_.currentClient();
	game_.sendToCurrentPlayer("de prediker krijgt voor elk blauw gebouw 1 goudstuk");
	auto count = 0;
	std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard& card) 
	{
		if (card.color() == card.BLAUW && card.owner() == player.get_player().ownertag() && card.active()) {
			count++;
		}
	});
	
	game_.sendToCurrentPlayer("je bezit " + std::to_string(count) + " blauwe gebouwen");
	player.get_player().gold(player.get_player().gold() + count);
	game_.sendToCurrentPlayer("je bezit nu " + std::to_string(player.get_player().gold()) + " goudstukken");
	game_.sendToCurrentPlayer("druk op enter om verder te gaan");
	used_ = true;
}

bool Prediker::act(ClientInfo & clientInfo, std::string cmd)
{
	return true;
}

void Prediker::onLeave()
{
	used_ = false;
	mugged_ = false;
}

void Prediker::name(std::string const name)
{
	name_ = name;
}

std::string const Prediker::name() const
{
	return name_;
}

bool Prediker::usable() const
{
	return !used_;
}

void Prediker::removeBuildingCard(int index)
{
	game_.sendToCurrentPlayer("de gebouwen van de prediker kunnen niet verwijderd worden");
}

