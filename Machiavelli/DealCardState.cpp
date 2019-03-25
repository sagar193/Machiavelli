#include "State.h"
#include "pch.h"
#include "DealCardState.h"
#include "Bouwmeester.h"
#include <algorithm>
#include "Game.h"
#include "ClientInfo.h"
#include "random.h"

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
	
	if (this->game_.client1().get_player().isKing()) 
	{
		game_.sendToAllPlayers("speler1 is de koning");
		game_.sendToAllPlayers("speler1 is aan de beurt");
		game_.setCurrentClient(Game::Players::Player1);
	}
	else if (game_.client2().get_player().isKing()) 
	{
		game_.sendToAllPlayers("speler2 is de koning");
		game_.sendToAllPlayers("speler2 is aan de beurt");
		game_.setCurrentClient(Game::Players::Player2);
	}
	else
	{
		if (game_.client1().get_player().age() >= game_.client2().get_player().age()) {
			game_.client1().get_player().isKing(true);
			game_.sendToAllPlayers("speler1 is de koning");
			game_.sendToAllPlayers("speler1 is aan de beurt");
			game_.setCurrentClient(Game::Players::Player1);
		}
		else {
			game_.client2().get_player().isKing(true);
			game_.sendToAllPlayers("speler2 is de koning");
			game_.sendToAllPlayers("speler2 is aan de beurt");
			game_.setCurrentClient(Game::Players::Player2);
		}
	}
	
	//todo: reset all charactercards
	const int toRemove = random_int(0, 7);
	game_.characterCards()[toRemove]->owner(None);
	game_.sendToCurrentPlayer(game_.characterCards()[toRemove]->name() + " (" + std::to_string(toRemove+1) + ") is weggelegd en doet deze ronde niet mee.");
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
