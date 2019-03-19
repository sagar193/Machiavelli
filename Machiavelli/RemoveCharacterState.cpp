#include "pch.h"
#include "RemoveCharacterState.h"
#include "ClientInfo.h"
#include <algorithm>

RemoveCharacterState::RemoveCharacterState(Game& game) : State(game)
{

}

bool RemoveCharacterState::act(ClientInfo & clientInfo, std::string cmd)
{
	clientInfo.get_socket() << "kies een van de volgende kaarten om weg te leggen" << "\r\n";

	int count = 1;
	std::for_each(game_.characterCards().begin(), game_.characterCards().end(), [&](const std::unique_ptr<CharacterCard>& card)
	{
		if (card->owner() == CharacterCard::Owner::Deck)
		{
			clientInfo.get_socket() << count << ": " << card->name() << "\r\n";
		}
		count++;
	});

	int cmdi = std::stoi(cmd) - 1;
	if (cmdi > 0 && cmdi < game_.characterCards().size() && game_.characterCards()[cmdi]->owner() == CharacterCard::Owner::Deck) {
		game_.characterCards()[cmdi]->owner(CharacterCard::Owner::None);
		return true;
	}

	return false;
}


RemoveCharacterState::~RemoveCharacterState()
{
}
