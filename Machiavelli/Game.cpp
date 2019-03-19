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
	//characterCards_.push_back(std::make_unique<Dief>());
	//characterCards_.push_back(std::make_unique<Magier>());
	//characterCards_.push_back(std::make_unique<Koning>());
	//characterCards_.push_back(std::make_unique<Prediker>());
	//characterCards_.push_back(std::make_unique<Koopman>());
	//characterCards_.push_back(std::make_unique<Bouwmeester>());
	//characterCards_.push_back(std::make_unique<Condottiere>());
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
	}
	else if (client_info2 == nullptr) {
		client_info2 = clientInfo;
		client_info2->get_socket() << "jij bent speler2";
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
		currentState_->act(*clientInfo, cmd);
	}
	else {
		clientInfo->get_socket() << "je bent niet aan de beurt";
	}
}



//void Game::setPlayer(Player& const player)
//{
	//players_[Players::Player1] = std::make_unique<Player>();
	//if (player1_ == nullptr) {
	//	player1_ = &player;
	//	player1_->socket() << "jij bent speler1";
	//}
	//else if (player2_ == nullptr) {
	//	player2_ = &player;
	//	player2_->socket() << "jij bent speler2";
	//}
	//else {
	//	//todo: je moet eerst iets schrijven is niet mooi nicht richtig
	//	player.socket() << "fuck off, game is full!!!!!!!!!!";
	//	throw std::exception("Game already full");
	//}
	//
	//if (player1_ != nullptr && player2_ != nullptr) {
	//	startGame();
	//}
//}

//void Game::handleCommand(Player & const player, std::string cmd)
//{
//	
//}

void Game::startGame()
{
	if (client_info1->get_player().age()>= client_info2->get_player().age()) {
		client_info1->get_socket() << "jij bent koning!";
		client_info2->get_socket() << "speler1 is koning";
		client_info1->get_player().isKing(true);
		currentClient_ = &(*client_info1);
		
	}
	else {
		client_info2->get_socket() << "jij bent koning!";
		client_info1->get_socket() << "speler2 is koning";
		client_info2->get_player().isKing(true);
		currentClient_ = &(*client_info2);
	}
	
	currentState_ = states_[States::DealCards].get();

	//if (player1_->age() >= player2_->age()) {
	//	player1_->socket() << "jij bent koning!";
	//	player2_->socket() << "speler1 is koning";
	//	player1_->isKing(true);
	//	
	//}
	//else {
	//	player2_->socket() << "jij bent koning!";
	//	player1_->socket() << "speler2 is koning";
	//	player2_->isKing(true);
	//}
	//
	//currentState_ = nullptr;
}


Game::~Game()
{
}
