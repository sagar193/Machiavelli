#include "pch.h"
#include "DealCardState.h"
#include "Bouwmeester.h"
#include <algorithm>

DealCardState::DealCardState(Game& game) : State(game),chooseCharacterState(game), removeCharacterState(game)
{
	currentState = &chooseCharacterState;
	firstTurn = true;
}

void DealCardState::onEnter()
{
	//todo: remove random card
	//todo: setstate
	game_.characterCards()[0]->owner(CharacterCard::None);
	currentState->onEnter();
}

bool DealCardState::act(ClientInfo& clientInfo,std::string cmd)
{
	auto callback = currentState->act(clientInfo, cmd);
	if (callback == true) {
		if (currentState == &chooseCharacterState) {
			if (firstTurn) 
			{
				firstTurn = false;
				game_.switchCurrentClientInfo();
				currentState->onEnter();
				game_.currentClient().get_socket() << "de andere speler mag nu kiezen\r\n";
				return true;
			}
			currentState = &removeCharacterState;
			currentState->onEnter();
			return false;
		}
		else if (currentState == &removeCharacterState && !firstTurn) {
			currentState = &chooseCharacterState;
			
			int totalLeft = std::count_if(game_.characterCards().begin(), game_.characterCards().end(), [](std::unique_ptr<CharacterCard>& card)
			{
				if (card->owner() == CharacterCard::Deck) {
					return true;
				} 
				return false;
			});

			if (totalLeft == 0) {
				game_.setState(Game::States::Playing);
				game_.currentState().onEnter();
				firstTurn = true;
			}
			else {
				game_.currentClient().get_socket() << "de andere speler mag nu kiezen\r\n";
				game_.switchCurrentClientInfo();
				currentState->onEnter();
			}
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
