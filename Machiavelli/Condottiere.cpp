#include "pch.h"
#include "Condottiere.h"
#include "ClientInfo.h"
#include "Game.h"
#include <algorithm>

void Condottiere::printOtherPlayerBuildingCards()
{
	int count = 1;
	auto& player = game_.currentClient();
	std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard& card)
	{
		auto b1 = player.get_player().ownertag() == Owner::Player1 && card.owner() == Owner::Player2;
		auto b2 = player.get_player().ownertag() == Owner::Player2 && card.owner() == Owner::Player1;
		if ((b1||b2)&& card.active()) {
			game_.sendToCurrentPlayer("\t" + std::to_string(count) + "| Kaartnaam: " + card.name() + "| Kosten: " + std::to_string(card.cost() -1) +
				"| kleur: " + card.colorString());
		}
		count++;
	});
}

bool Condottiere::prediker()
{
	bool can = true;
	auto& player = game_.currentClient().get_player();
	std::for_each(game_.characterCards().begin(), game_.characterCards().end(), [&](std::unique_ptr<CharacterCard>& card)
	{
		auto b1 = player.ownertag() == Owner::Player1 && card->owner() == Owner::Player2;
		auto b2 = player.ownertag() == Owner::Player2 && card->owner() == Owner::Player1;
		if ((b1 || b2) && card->name() == "Prediker") {
			can = false;
		}
	});
	return can;
}

bool Condottiere::eightBuildings()
{
	int count = 0;
	auto& player = game_.currentClient().get_player();
	std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard& card)
	{
		auto b1 = player.ownertag() == Owner::Player1 && card.owner() == Owner::Player2;
		auto b2 = player.ownertag() == Owner::Player2 && card.owner() == Owner::Player1;
		if ((b1 || b2) && card.active()) {
			count++;
		}
	});
	return count < 8;
}

int Condottiere::calcBuilding()
{
	int count = 0;
	auto& player = game_.currentClient().get_player();
	std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard& card)
	{
		if (card.owner() == player.ownertag() && card.color() == BuildingCard::ROOD && card.active()) {
			count++;
		}
	});
	return count;
}

Condottiere::Condottiere(Game& game)  : CharacterCard(game)
{
	this->name_ = "Condonttiere";
	characterCardIdentifier_ = CharacterCardEnum::CONDOTTIERE;
	mugged_ = false;
	canChoose = true;
	gotGold = false;
}


Condottiere::~Condottiere()
{
}

void Condottiere::onEnter()
{
	if (canChoose) 
	{
		if (!gotGold) {
			auto count = calcBuilding();
			auto& player = game_.currentClient().get_player();
			game_.sendToCurrentPlayer("je hebt " + std::to_string(count) + " rode gebouwen en krijgt dus " + std::to_string(count) + " gpudstukken");
			player.gold(player.gold() + count);
			game_.sendToCurrentPlayer("je hebt nu " +std::to_string(player.gold())+" goudstukken");
			gotGold = true;
		}

		if (!prediker()) 
		{
			game_.sendToCurrentPlayer("de andere speler is een prediker dus mag er niks in de stad kapot");
			canChoose = false;
		}
		else if (!eightBuildings()) 
		{
			game_.sendToCurrentPlayer("de andere speler heeft 8 gebouwen dus mag er niks in de stad kapot");
			canChoose = false;
		}
		else 
		{
			game_.sendToCurrentPlayer("kies uit een van de volgende kaarten om ze vernietigen");
			printOtherPlayerBuildingCards();
			return;
		}
	}
	else 
	{
		game_.sendToCurrentPlayer("je mag maar 1 gebouw per ronde vernietigen");
	}
	game_.sendToCurrentPlayer("druk op enter om verder te gaan");
}

void Condottiere::onLeave()
{
	canChoose = true;
	mugged_ = false;
	gotGold = false;
}

bool Condottiere::act(ClientInfo & clientInfo, std::string cmd)
{
	if (canChoose) {
		if (!cmd.empty()) {
			int cmdi = std::stoi(cmd) -1;
			if (cmdi >= 0 && cmdi < game_.buildingCards().size()) {
				
				auto& card = game_.buildingCards()[cmdi];
				auto& player = game_.currentClient().get_player();
				int cost = card.cost() - 1;

				auto b1 = player.ownertag() == Owner::Player1 && card.owner() == Owner::Player2;
				auto b2 = player.ownertag() == Owner::Player2 && card.owner() == Owner::Player1;


				if (card.active() && (b1 || b2) && player.gold()>=cost) {
					game_.buildingCards()[cmdi].owner(Owner::None);
					game_.buildingCards()[cmdi].active(false);
					int newGold = game_.currentClient().get_player().gold() - cost;
					game_.currentClient().get_player().gold(newGold);
					game_.sendToCurrentPlayer(card.name()+" is nu vernietigd");
					game_.sendToCurrentPlayer("je hebt nu nog "+std::to_string(player.gold())+" goudstukken");
					canChoose = false;
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

