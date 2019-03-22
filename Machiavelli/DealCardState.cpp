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
	//todo: setking
	
	if (game_.client1().get_player().isKing()) 
	{
		game_.client1().get_socket() << "jij bent koning!";
		game_.client2().get_socket() << "speler1 is koning";
		game_.setCurrentClient(Game::Players::Player1);
	}
	else if (game_.client2().get_player().isKing()) 
	{
		game_.client2().get_socket() << "jij bent koning!";
		game_.client1().get_socket() << "speler2 is koning";
		game_.setCurrentClient(Game::Players::Player2);
	}
	else
	{
		if (game_.client1().get_player().age() >= game_.client2().get_player().age()) {
			game_.client1().get_player().isKing(true);
			game_.client1().get_socket() << "jij bent koning!";
			game_.client2().get_socket() << "speler1 is koning";
			game_.setCurrentClient(Game::Players::Player1);
		}
		else {
			game_.client2().get_player().isKing(true);
			game_.client2().get_socket() << "jij bent koning!";
			game_.client1().get_socket() << "speler2 is koning";
			game_.setCurrentClient(Game::Players::Player2);
		}
	}
	
	//todo: reset all charactercards
	game_.characterCards()[0]->owner(None);
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
				game_.currentClient().get_socket() << "/r/nDe andere speler mag nu kiezen\r\n";
				game_.switchCurrentClientInfo();
				currentState->onEnter();
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
				if (card->owner() == Owner::Deck) {
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
		if (card->owner() == Owner::Deck)
		{
			clientInfo.get_socket() << count << ": " << card->name() <<"\r\n";
		}
		count++;
	});
}


DealCardState::~DealCardState()
= default;
