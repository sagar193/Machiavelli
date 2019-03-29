#include "pch.h"
#include "Moordenaar.h"
#include "ClientInfo.h"
#include "Game.h"
#include <algorithm>

Moordenaar::Moordenaar(Game& game) : CharacterCard(game)
{
	this->name_ = "Moordenaar";
	characterCardIdentifier_ = CharacterCardEnum::MOORDENAAR;
	mugged_ = false;
}


Moordenaar::~Moordenaar()
{
}

void Moordenaar::onEnter()
{
	this->game_.sendToCurrentPlayer("Welke karakter wil je vermoorden?");
	printAllCharacters();
}

void Moordenaar::onLeave()
{
	mugged_ = false;
}

bool Moordenaar::act(ClientInfo & clientInfo, std::string cmd)
{
	if (!cmd.empty()) {
		int cmdi = std::stoi(cmd) - 1;
		if (cmdi >= 0 && cmdi < game_.characterCards().size() - 1) {
			CharacterCard& chosenCard = *game_.characterCards().at(cmdi + 1);
			chosenCard.owner(Owner::Killed);
			game_.sendToAllPlayers("De moordenaar heeft de " + chosenCard.name() + " vermoord.");
			return true;
		}
	}
	this->game_.sendToCurrentPlayer("Ongeldige input.");
	printAllCharacters();

	return false;
}

bool Moordenaar::mugged(bool const mugged)
{
	if (mugged == true) {
		game_.sendToCurrentPlayer("De moordenaar kan niet beroofd worden.");
		return false;
	}
	else {
		return true;
	}
}

void Moordenaar::printAllCharacters() const
{
	int count = 1;
	std::for_each(game_.characterCards().begin()+1, game_.characterCards().end(), [&](const std::unique_ptr<CharacterCard>& card)
	{
		if (card->owner() != Owner::Killed) {
			game_.sendToCurrentPlayer(std::to_string(count) + ": " + card->name());

		}
		count++;
	});
}


void Moordenaar::rank(int const rank)
{
	rank_ = rank;
}

int const Moordenaar::rank() const
{
	return rank_;
}

void Moordenaar::name(std::string const name)
{
	name_ = name;
}

std::string const Moordenaar::name() const
{
	return name_;
}
