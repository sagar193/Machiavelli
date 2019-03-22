#include "pch.h"
#include "Game.h"
#include "DealCardState.h"
#include "PlayingState.h"
#include "State.h"
#include "ClientInfo.h"
#include "Moordenaar.h"
#include "Dief.h"
#include "Magier.h"
#include "Koning.h"
#include "Prediker.h"
#include "Koopman.h"
#include "Bouwmeester.h"
#include "Condottiere.h"

//todo: player1 leave 

void Game::loadCharacterCards()
{
	characterCards_.push_back(std::make_unique<Moordenaar>());
	characterCards_.push_back(std::make_unique<Dief>());
	characterCards_.push_back(std::make_unique<Magier>());
	characterCards_.push_back(std::make_unique<Koning>());
	characterCards_.push_back(std::make_unique<Prediker>());
	characterCards_.push_back(std::make_unique<Koopman>());
	characterCards_.push_back(std::make_unique<Bouwmeester>());
	characterCards_.push_back(std::make_unique<Condottiere>());
}

void Game::switchCurrentClientInfo()
{
	currentClient().get_socket() << "de andere speler is nu aan de beurt\r\n";
	if (&(*client_info1) == currentClient_)
		currentClient_ = &(*client_info2);
	else
		currentClient_ = &(*client_info1);
}

void Game::setCurrentClient(Players player)
{
	if (player == Players::Player1) 
	{
		currentClient_ = &(*client_info1);
	}
	else if (player == Players::Player2)
	{
		currentClient_ = &(*client_info2);
	}
}

Game::Game()
{
	client_info1 = nullptr;
	client_info2 = nullptr;
	//player1_ = nullptr;
	//player2_ = nullptr;
	

	states_[Game::States::DealCards] = std::make_unique<DealCardState>(*this);
	states_[Game::States::Playing] = std::make_unique<PlayingState>(*this);
	currentState_ = nullptr;
	loadCharacterCards();
}

void Game::setPlayer(std::shared_ptr<ClientInfo> const clientInfo)
{
	if (client_info1 == nullptr) {
		client_info1 = clientInfo;
		client_info1->get_socket() << "jij bent speler1";
		client_info1->get_player().ownertag(Owner::Player1);
	}
	else if (client_info2 == nullptr) {
		client_info2 = clientInfo;
		client_info2->get_socket() << "jij bent speler2";
		client_info2->get_player().ownertag(Owner::Player2);
	}
	else {
		//todo: je moet eerst iets schrijven is niet mooi nicht richtig
		clientInfo->get_socket() << "fuck off, game is full!!!!!!!!!!";
		throw std::exception("Game already full");
	}
	
	if (client_info1 != nullptr && client_info2 != nullptr) {
		startGame();
	}
}

void Game::handleCommand(std::shared_ptr<ClientInfo> const clientInfo, std::string cmd)
{
	if (currentClient_ == &(*clientInfo)) {
		auto callback = currentState_->act(*clientInfo, cmd);
		if (callback == true) {
			//if ()
			//{
			//	currentState_ = states_[States::Playing].get();
			//}
			//else {
			//	switchCurrentClientInfo();
			//	currentState_->onEnter();
			//}
		}

	}
	else {
		clientInfo->get_socket() << "je bent niet aan de beurt";
	}
}

void Game::sendToCurrentPlayer(const std::string message) const
{
	currentClient_->get_socket() << message << "/r/n";
}

void Game::setState(States state)
{
	currentState_ = states_[state].get();
}



void Game::startGame()
{
	
	
	currentState_ = states_[States::DealCards].get();
	currentState_->onEnter();

	
}


Game::~Game()
{
}
