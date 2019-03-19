#include "pch.h"
#include "DealCardState.h"
#include "ClientInfo.h"
#include "Bouwmeester.h"


DealCardState::DealCardState(Game& game) : State(game),chooseCharacterState(game), removeCharacterState(game)
{
	currentState = &chooseCharacterState;
}

void DealCardState::onEnter()
{
}

bool DealCardState::act(ClientInfo& clientInfo,std::string cmd)
{
	auto callback = currentState->act(clientInfo, cmd);
	if (callback == true) {
		if (currentState == &chooseCharacterState) {
			currentState = &removeCharacterState;
			return false;
		}
		else if (currentState == &removeCharacterState) {
			currentState = &chooseCharacterState;
			return true;
		}
	}

	return false;
}

void DealCardState::onLeave()
{
}

void DealCardState::printCharacterCards(ClientInfo & clientInfo)
{

	int count = 1;
	std::for_each(game_.characterCards().begin(), game_.characterCards().end(), [&](const std::unique_ptr<CharacterCard>& card)
	{
		if (card->owner() == CharacterCard::Owner::Deck)
		{
			clientInfo.get_socket() << count << ": " << card->name() <<"\r\n";
		}
		count++;
	});
}


DealCardState::~DealCardState()
= default;
