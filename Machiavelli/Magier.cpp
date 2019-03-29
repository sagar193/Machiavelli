#include "pch.h"
#include "Magier.h"
#include "ClientInfo.h"
#include "Game.h"
#include <algorithm>
#include "random.h"

Magier::Magier(Game& game) : CharacterCard(game)
{
	this->name_ = "Magier";
	characterCardIdentifier_ = CharacterCardEnum::MAGIER;
	mugged_ = false;
}


Magier::~Magier()
{
}

void Magier::onEnter()
{
	this->game_.sendToCurrentPlayer("Toets 1 om alle handkaarten om te ruilen met de andere speler");
	this->game_.sendToCurrentPlayer("Toets 2 om je kaarten handkaarten weg te doen en een even aantal gebouwenkaarten te trekken");
}

void Magier::onLeave()
{
	mugged_ = false;
}

bool Magier::act(ClientInfo & clientInfo, std::string cmd)
{
	if (!cmd.empty()) {
		int cmdi = std::stoi(cmd);
		if (cmdi == 1) {
			std::vector<BuildingCard*> player1Cards;
			int count = 1;
			std::vector<BuildingCard*> player2Cards;
			std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard& card)
			{
				if (card.owner() == Player1 && card.active() == false)
				{
					player1Cards.push_back(&card);
				}
				if (card.owner() == Player2 && card.active() == false)
				{
					player2Cards.push_back(&card);
				}
			});
			std::for_each(player1Cards.begin(), player1Cards.end(), [&](BuildingCard* card) {
				card->owner(Player2);
			});
			std::for_each(player2Cards.begin(), player2Cards.end(), [&](BuildingCard* card) {
				card->owner(Player1);
			});
			return true;

		}
		else if (cmdi == 2) {
			std::vector<BuildingCard*> activePlayerBuildings;
			std::for_each(game_.buildingCards().begin(), game_.buildingCards().end(), [&](BuildingCard& card){
				if (card.owner() == game_.currentPlayer().ownertag() && card.active() == false)
				{
					activePlayerBuildings.push_back(&card);
				}
			});
			for (size_t i = 0; i < activePlayerBuildings.size(); i++)
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
				game_.buildingCards().at(randomint).owner(game_.currentPlayer().ownertag());
			}
			std::for_each(activePlayerBuildings.begin(), activePlayerBuildings.end(), [&](BuildingCard* card) {
				card->owner(None);
			});

			return true;
		}
	}
	this->game_.sendToCurrentPlayer("Ongeldige input.");
	onEnter();

	return false;
}


void Magier::rank(int const rank)
{
	rank_ = rank;
}

int const Magier::rank() const
{
	return rank_;
}

void Magier::name(std::string const name)
{
	name_ = name;
}

std::string const Magier::name() const
{
	return name_;
}

