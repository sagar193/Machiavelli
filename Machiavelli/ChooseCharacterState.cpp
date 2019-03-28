#include "pch.h"
#include "ChooseCharacterState.h"
#include <algorithm>
#include "ClientInfo.h"
#include "Game.h"

ChooseCharacterState::ChooseCharacterState(Game& game) : State(game)
{
}

void ChooseCharacterState::onEnter()
{
	game_.currentClient().get_socket() << "kies een van de volgende kaarten" << "\r\n";

	int count = 1;
	std::for_each(game_.characterCards().begin(), game_.characterCards().end(), [&](const std::unique_ptr<CharacterCard>& card)
	{
		if (card->owner() == Deck)
		{
			game_.currentClient().get_socket() << count << ": " << card->name() << "\r\n";
		}
		count++;
	});
}

bool ChooseCharacterState::act(ClientInfo & clientInfo, std::string cmd)
{
	//clientInfo.get_socket() << "kies een van de volgende kaarten" << "\r\n";
	//
	//int count = 1;
	//std::for_each(game_.characterCards().begin(), game_.characterCards().end(), [&](const std::unique_ptr<CharacterCard>& card)
	//{
	//	if (card->owner() == CharacterCard::Owner::Deck)
	//	{
	//		clientInfo.get_socket() << count << ": " << card->name() << "\r\n";
	//	}
	//	count++;
	//});

	if (!cmd.empty()) {
		int cmdi = std::stoi(cmd) - 1;
		if (cmdi >= 0 && cmdi < game_.characterCards().size() && game_.characterCards()[cmdi]->owner() == Owner::Deck) {
			game_.characterCards()[cmdi]->owner(clientInfo.get_player().ownertag());
			return true;
		}
		else {
			game_.sendToCurrentPlayer("Ongeldige input.");
			onEnter();
		}
	}

	return false;
}


ChooseCharacterState::~ChooseCharacterState()
{
}
