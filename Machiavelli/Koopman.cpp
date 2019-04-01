#include "pch.h"
#include "Koopman.h"
#include "ClientInfo.h"
#include "game.h"
#include <algorithm>

Koopman::Koopman(Game& game) : CharacterCard(game)
{
	this->name_ = "Koopman";
	characterCardIdentifier_ = CharacterCardEnum::KOOPMAN;
	mugged_ = false;
	used_ = false;
}


Koopman::~Koopman()
{
}

void Koopman::onEnter()
{
	if (used_) {
		game_.sendToCurrentPlayer("deze kaart is al gebruikt druk op enter om verder te gaan");
		return;
	}
	auto& player = game_.currentClient();
	game_.sendToCurrentPlayer("de koopman krijgt bij iedere beurt 1 goudstuk plus 1 voor elk groen gebouw");
	auto count = 0;
	std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard& card)
	{
		if (card.color() == card.GROEN && card.owner() == player.get_player().ownertag() && card.active()) {
			count++;
		}
	});

	game_.sendToCurrentPlayer("je bezit " + std::to_string(count) + " groene gebouwen");
	player.get_player().gold(player.get_player().gold() + count+1);
	game_.sendToCurrentPlayer("je bezit nu " + std::to_string(player.get_player().gold()) + " goudstukken");
	game_.sendToCurrentPlayer("druk op enter om verder te gaan");
}

void Koopman::onLeave()
{
	used_ = false;
	mugged_ = false;
}

bool Koopman::act(ClientInfo & clientInfo, std::string cmd)
{
	used_ = true;
	return true;
}

void Koopman::name(std::string const name)
{
	name_ = name;
}

std::string const Koopman::name() const
{
	return name_;
}

bool Koopman::usable() const
{
	return !used_;
}

