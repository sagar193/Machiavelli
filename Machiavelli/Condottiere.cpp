#include "pch.h"
#include "Condottiere.h"
#include "ClientInfo.h"
#include "Game.h"
#include <algorithm>

//todo
void Condottiere::printOtherPlayerBuildingCards()
{
	int count = 0;
	auto& player = game_.currentClient();
	std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard& card)
	{
		if (card.owner() != player.get_player().ownertag() && card.active()) {
			game_.sendToCurrentPlayer(std::to_string(count) + ": " + card.name() + " |kost: "+ std::to_string(card.cost()-1) + " goustukken om te vernietigen");
		}
		count++;
	});
}

Condottiere::Condottiere(Game& game)  : CharacterCard(game)
{
	this->name_ = "Condonttiere";
	characterCardIdentifier_ = CharacterCardEnum::CONDOTTIERE;
	mugged_ = false;
	canChoose = true;
}


Condottiere::~Condottiere()
{
}

void Condottiere::onEnter()
{
	bool can = true;
	auto& player = game_.currentClient().get_player();
	std::for_each(game_.characterCards().begin(), game_.characterCards().end(), [&](std::unique_ptr<CharacterCard>& card) 
	{
		auto b1 = player.ownertag() == Owner::Player1 && card->owner() == Owner::Player2;
		auto b2 = player.ownertag() == Owner::Player2 && card->owner() == Owner::Player1;
		if (b1 || b2) {
			can = false;
		}
	});
	canChoose = can;
	if (canChoose) {
		game_.sendToCurrentPlayer("kies uit een van de volgende kaarten om ze vernietigen");
		printOtherPlayerBuildingCards();
		return;
	}
	game_.sendToCurrentPlayer("de andere speler is een prediker en zijn gebouwen kunnen niet kapot");
	game_.sendToCurrentPlayer("druk op enter om verder te gaan");
}

void Condottiere::onLeave()
{
	canChoose = true;
	mugged_ = false;
}

bool Condottiere::act(ClientInfo & clientInfo, std::string cmd)
{
	if (canChoose) {
		if (!cmd.empty()) {
			int cmdi = std::stoi(cmd);
			if (cmdi >= 0 && cmdi < game_.buildingCards().size()) {
				
				auto& card = game_.buildingCards()[cmdi];
				auto& player = game_.currentClient().get_player();
				int cost = card.cost() - 1;

				auto b1 = player.ownertag() == Owner::Player1 && card.owner() == Owner::Player2;
				auto b2 = player.ownertag() == Owner::Player2 && card.owner() == Owner::Player1;


				if (card.active() && b1 && b2 && player.gold()>=cost) {
					game_.buildingCards()[cmdi].owner(Owner::None);
					int newGold = game_.currentClient().get_player().gold() - cost;
					game_.currentClient().get_player().gold(newGold);
					game_.sendToCurrentPlayer(card.name()+" is nu vernietigd");
					game_.sendToCurrentPlayer("je hebt nu nog "+std::to_string(player.gold())+" goudstukken");
					return true;
				}
			}
			game_.sendToCurrentPlayer("ongeldige keuze");
		}
	}
	return true;
}

bool Condottiere::usable() const
{
	return canChoose;
}

void Condottiere::name(std::string const name)
{
	name_ = name;
}

std::string const Condottiere::name() const
{
	return name_;
}

