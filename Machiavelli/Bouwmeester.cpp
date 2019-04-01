#include "pch.h"
#include "Bouwmeester.h"
#include "ClientInfo.h"
#include "Game.h"
#include "random.h"
#include <algorithm>

BuildingCard & Bouwmeester::getRandomBuildingCardFromDeck() const
{
	std::vector<int> unused;
	int count = 0;
	std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard& card)
	{
		if (card.owner() == Owner::Deck) {
			unused.push_back(count);
		}
		count++;
	});
	int randomint = random_int(0, unused.size() - 1);
	return game_.buildingCards().at(unused.at(randomint));

}

void Bouwmeester::printAllBuidlingCards()
{
	int count = 1;
	auto& player = game_.currentClient();
	std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard& card) 
	{
		if (card.owner() == player.get_player().ownertag() && !card.active()) {
			game_.sendToCurrentPlayer(std::to_string(count) + ": " + card.name());
		}
		count++;
	});
}

Bouwmeester::Bouwmeester(Game& game) : CharacterCard(game)
{
	this->name_ = "Bouwmeester";
	characterCardIdentifier_ = CharacterCardEnum::BOUWMEESTER;
	mugged_ = false;
	countPlacableBuildings = 3;
	hasdrawn_ = false;
}


Bouwmeester::~Bouwmeester()
{
}

void Bouwmeester::onEnter()
{
	if (!hasdrawn_) {
		game_.sendToCurrentPlayer("de Bouwmeester in 3 kaarten wegleggen als de Bouwmeester en krijgt 2 kaarten");
		auto drawnBuildingCard1 = &getRandomBuildingCardFromDeck();
		drawnBuildingCard1->owner(game_.currentPlayer().ownertag());
		auto drawnBuildingCard2 = &getRandomBuildingCardFromDeck();
		drawnBuildingCard2->owner(game_.currentPlayer().ownertag());
		game_.sendToCurrentPlayer("Je hebt de volgende kaarten getrokken: \r\n" +
			drawnBuildingCard1->name() + "\r\n" +
			drawnBuildingCard2->name() + "\r\n");
		hasdrawn_ = true;
	}
	if (countPlacableBuildings == 0) {
		game_.sendToCurrentPlayer("je kan geen kaarten meer plaatsen druk op enter om verder te gaan");
		return;
	}
	game_.sendToCurrentPlayer("je mag nog " + std::to_string(countPlacableBuildings) + " kaarten plaatsen");
	game_.sendToCurrentPlayer("je bezit op het moment deze kaarten");
	printAllBuidlingCards();
	game_.sendToCurrentPlayer("druk op 0 om terug te gaan");
}

bool Bouwmeester::act(ClientInfo & clientInfo, std::string cmd)
{
	if (countPlacableBuildings == 0) {
		return true;
	}
	if (!cmd.empty()) {
		int cmdi = std::stoi(cmd);
		int cardIndex = cmdi - 1;
		if (cmdi == 0) {
			return true;
		}
		if (cardIndex >= 0 && cardIndex < game_.buildingCards().size()) {
			auto card = game_.buildingCards()[cardIndex];
			if (card.owner() == game_.currentClient().get_player().ownertag() && !card.active()) {
				card.active(true);
				countPlacableBuildings--;
			}
		}
	}
	return false;
}

void Bouwmeester::onLeave()
{
	hasdrawn_ = false;
	countPlacableBuildings = 3;
	mugged_ = false;
}

bool Bouwmeester::usable() const
{
	if (hasdrawn_ == true && countPlacableBuildings == 0)
		return false;
	else
		return true;
}

void Bouwmeester::name(std::string const name)
{
	name_ = name;
}

std::string const Bouwmeester::name() const
{
	return name_;
}
