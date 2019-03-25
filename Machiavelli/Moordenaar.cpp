#include "pch.h"
#include "Moordenaar.h"
#include "ClientInfo.h"
#include "Game.h"
#include <algorithm>

Moordenaar::Moordenaar(Game& game) : CharacterCard(game)
{
	this->name_ = "Moordenaar";
}


Moordenaar::~Moordenaar()
{
}

void Moordenaar::onEnter()
{
	this->game_.sendToCurrentPlayer("Welke karakter wil je vermoorden?");
	printAllCharacters();
}

bool Moordenaar::act(ClientInfo & clientInfo, std::string cmd)
{
	if (!cmd.empty()) {
		int cmdi = std::stoi(cmd) - 1;
		if (cmdi >= 0 && cmdi < game_.characterCards().size()) {
			CharacterCard& chosenCard = *game_.characterCards().at(cmdi);
			chosenCard.owner(Owner::None);
			game_.sendToAllPlayers("De moordenaar heeft de " + chosenCard.name() + " vermoord.");
			return true;
		}
	}
	this->game_.sendToCurrentPlayer("Ongeldige input.");
	printAllCharacters();

	return false;
}

void Moordenaar::printAllCharacters() const
{
	int count = 1;
	std::for_each(game_.characterCards().begin(), game_.characterCards().end(), [&](const std::unique_ptr<CharacterCard>& card)
	{
		game_.sendToCurrentPlayer(std::to_string(count) + ": " + card->name());

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
