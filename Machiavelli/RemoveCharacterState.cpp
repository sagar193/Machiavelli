#include "pch.h"
#include "RemoveCharacterState.h"
#include <algorithm>
#include "ClientInfo.h"
#include "Game.h"

RemoveCharacterState::RemoveCharacterState(Game& game) : State(game)
{

}

void RemoveCharacterState::onEnter()
{
	game_.currentClient().get_socket() << "kies een van de volgende kaarten om weg te leggen" << "\r\n";

	int count = 1;
	std::for_each(game_.characterCards().begin(), game_.characterCards().end(), [&](const std::unique_ptr<CharacterCard>& card)
	{
		if (card->owner() == Owner::Deck)
		{
			game_.currentClient().get_socket() << count << ": " << card->name() << "\r\n";
		}
		count++;
	});
}

bool RemoveCharacterState::act(ClientInfo & clientInfo, std::string cmd)
{
	if (!cmd.empty()) {
		int cmdi = std::stoi(cmd) - 1;
		if (cmdi > 0 && cmdi < game_.characterCards().size() && game_.characterCards()[cmdi]->owner() == Owner::Deck) {
			game_.characterCards()[cmdi]->owner(Owner::None);
			return true;
		}
	}

	return false;
}


RemoveCharacterState::~RemoveCharacterState()
{
}
