#include "pch.h"
#include "Dief.h"
#include "ClientInfo.h"
#include "Game.h"
#include <algorithm>

Dief::Dief(Game& game) : CharacterCard(game)
{
	this->name_ = "Dief";
	characterCardIdentifier_ = CharacterCardEnum::DIEF;
	mugged_ = false;
}


Dief::~Dief()
{
}

void Dief::onEnter()
{
	this->game_.sendToCurrentPlayer("Welke karakter wil je bestelen?");
	printAllCharacters();
}

void Dief::onLeave()
{
	mugged_ = false;
}

bool Dief::act(ClientInfo & clientInfo, std::string cmd)
{
	if (!cmd.empty()) {
		int cmdi = std::stoi(cmd) - 1;
		if (cmdi >= 0 && cmdi < game_.characterCards().size()) {
			CharacterCard& chosenCard = *game_.characterCards().at(cmdi);
			if (chosenCard.owner() == Killed) {
				game_.sendToCurrentPlayer("Deze speler is deze ronde al vermoord, kies een andere character.");
				printAllCharacters();
				return false;
			}
				
			bool success = chosenCard.mugged(true);
			if (success == true) {
				game_.sendToAllPlayers("De dief heeft de " + chosenCard.name() + " beroofd.");
				return true;
			}
			else {
				printAllCharacters();
				return false;
			}
		}
	}
	this->game_.sendToCurrentPlayer("Ongeldige input.");
	printAllCharacters();

	return false;
}

void Dief::printAllCharacters() const
{
	int count = 1;
	std::for_each(game_.characterCards().begin(), game_.characterCards().end(), [&](const std::unique_ptr<CharacterCard>& card)
	{
		game_.sendToCurrentPlayer(std::to_string(count) + ": " + card->name());

		count++;
	});
}

void Dief::name(std::string const name)
{
	name_ = name;
}

std::string const Dief::name() const
{
	return name_;
}

bool Dief::usable() const
{
	return false;
}

