#include "pch.h"
#include "ChooseCharacterState.h"
#include <algorithm>
#include "ClientInfo.h"


ChooseCharacterState::ChooseCharacterState(Game& game) : State(game)
{
}

bool ChooseCharacterState::act(ClientInfo & clientInfo, std::string cmd)
{
	clientInfo.get_socket() << "kies een van de volgende kaarten" << "\r\n";

	int count = 1;
	std::for_each(game_.characterCards().begin(), game_.characterCards().end(), [&](const std::unique_ptr<CharacterCard>& card)
	{
		if (card->owner() == CharacterCard::Owner::Deck)
		{
			clientInfo.get_socket() << count << ": " << card->name() << "\r\n";
		}
		count++;
	});

	if (!cmd.empty()) {
		int cmdi = std::stoi(cmd) - 1;
		if (cmdi >= 0 && cmdi < game_.characterCards().size() && game_.characterCards()[cmdi]->owner() == CharacterCard::Owner::Deck) {
			game_.characterCards()[cmdi]->owner(clientInfo.get_player().ownertag());
			return true;
		}
	}

	return false;
}


ChooseCharacterState::~ChooseCharacterState()
{
}
